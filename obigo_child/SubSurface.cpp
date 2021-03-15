#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include "SubSurface.h"

extern struct wl_display *display;
extern struct wl_compositor *compositor;
extern struct ivi_application *iviapplication;
extern struct wl_shm *shm;

const int WIDTH = 250;
const int HEIGHT = 250;

static int create_shared_fd(off_t size) {
    fprintf(stdout, "[ObigoChild] create_shared_fd\n"); fflush(stdout);
    char name[1024] = "";

    const char *path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        exit(1);
    }

    strcpy(name, path);
    strcat(name, "/shm-test");

    int fd = open(name, O_RDWR | O_EXCL | O_CREAT, 777);
    if (fd < 0) {
        exit(1);
    } else {
        unlink(name);
    }

    if (ftruncate(fd, size) < 0) {
        close(fd);
        exit(1);
    }

    return fd;
}

static void* create_window(struct wl_surface *surface) {
    fprintf(stdout, "[ObigoChild] create_window\n"); fflush(stdout);
    int stride = WIDTH * 4;  // 4 bytes per pixel
    int size = stride * HEIGHT;

    int fd = create_shared_fd(size);
    void *shm_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_data == MAP_FAILED) {
        close(fd);
        exit(1);
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, WIDTH, HEIGHT, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);

    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_commit(surface);
    return shm_data;
}

static void paint_pixels(uint32_t *pixel) {
    fprintf(stdout, "[ObigoChild] paint_pixels\n"); fflush(stdout);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int mx = x / 20;
            int my = y / 20;
            uint32_t color = 0;
            if (mx % 2 == 0 && my % 2 == 0) {
                uint32_t code = (mx / 2) % 8;  // X axis determines a color code from 0 to 7.
                uint32_t red = code & 1 ? 0xff0000 : 0;
                uint32_t green = code & 2 ? 0x00ff00 : 0;
                uint32_t blue = code & 4 ? 0x0000ff : 0;
                uint32_t alpha = (my / 2) % 8 * 32 << 24;  // Y axis determines alpha value from 0 to 0xf0
                color = alpha + red + green + blue;
            }
            pixel[x + (y * WIDTH)] = color;
        }
    }
}

SubSurface::SubSurface() {
    m_wlsurface = nullptr;
    m_ivisurface = nullptr;
}

SubSurface::~SubSurface() {}

void SubSurface::CreateSurface(int32_t surfaceid) {
    m_wlsurface = wl_compositor_create_surface(compositor);
    m_ivisurface = ivi_application_surface_create(iviapplication, surfaceid, m_wlsurface);

    fprintf(stdout, "[ObigoChild] wl_compositor_create_surface : %p\n", m_wlsurface); fflush(stdout);
    fprintf(stdout, "[ObigoChild] ivi_application_surface_create : %p\n", m_ivisurface); fflush(stdout);

    void *shm_data = create_window(m_wlsurface);
    paint_pixels(static_cast<uint32_t*>(shm_data));
    wl_display_flush(display);
}