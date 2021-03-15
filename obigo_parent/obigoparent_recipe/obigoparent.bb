SUMMARY = "exampleapp"
DESCRIPTION = "HMIAppService Sample Application"
AUTHOR = "Hyejin Park"
SECTION = "ccOS/app/template"

inherit ccos-base-apps
inherit ccos-qmake
inherit ccos-systemd

DEPENDS += "hmiappcommon"

CCOS_VERSION = "7_796054360ccffc1a0611934226021fe9a1baba9b"
PR = "r1"

deltask ccos_sanity_check
CCOS_REPO_NAME = "exampleApp"
CCOS_GIT_BRANCH_NAME = "dev"
CCOS_GIT_REPO_PREFIX = "git://repo.ccos.dev:7999/~zzz6882_mobis.co.kr"
SRCREV = "${AUTOREV}"

