#ifndef __mohface_H__
#define __mohface_H__

#include <watch_app.h>
#include <watch_app_efl.h>
#include <Elementary.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "mohface"

#if !defined(PACKAGE)
#define PACKAGE "com.github.rlegendi.mohface"
#endif

#define APP_DIR						"/opt/usr/home/owner/apps_rw/com.github.rlegendi.mohface"
#define ICON_DIR 					APP_DIR"/shared/res"

#endif /* __mohface_H__ */
