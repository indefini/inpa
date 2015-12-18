#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <Ecore_X.h>
#include <Ecore_Evas.h>
#include "inpa_imcontext.h"

#include <Ecore.h>
#include <Ecore_IMF.h>
#include <Eldbus.h>

struct _InpaIMContext
{
   /* instance members */
   Ecore_IMF_Context *ctx;

   //IBusInputContext *ibuscontext;

   /* preedit status */
   char            *preedit_string;
   Eina_List       *preedit_attrs;
   int              preedit_cursor_pos;
   Eina_Bool        preedit_visible;

   int              cursor_x;
   int              cursor_y;
   int              cursor_w;
   int              cursor_h;

   Eina_Bool        has_focus;

   Ecore_X_Window   client_window;
   Evas            *client_canvas;

   Eldbus_Proxy *proxy;

   //int              caps;
};

#define BUS "org.Enlightenment"
#define PATH "/org/enlightenment"
#define INTERFACE "org.enlightenment.Test"
#define NTESTS 8
static int _client_log_dom = -1;
#define ERR(...)      EINA_LOG_DOM_ERR(_client_log_dom, __VA_ARGS__)

static Eldbus_Connection *conn = NULL;
static Ecore_Timer *timeout = NULL;

static void
_on_alive(void *context EINA_UNUSED, const Eldbus_Message *msg EINA_UNUSED)
{
   printf("Alive\n\n");
}
static void
_on_hello(void *context EINA_UNUSED, const Eldbus_Message *msg)
{
   const char *txt;
   if (eldbus_message_arguments_get(msg, "s", &txt))
     printf("%s\n", txt);
}


static void _init_dbus(InpaIMContext* c)
{
  Eldbus_Object *obj;
  Eldbus_Proxy *proxy;
  eina_init();
  ecore_init();
  eldbus_init();

  conn = eldbus_connection_get(ELDBUS_CONNECTION_TYPE_SESSION);
  obj = eldbus_object_get(conn, BUS, PATH);
  proxy = eldbus_proxy_get(obj, INTERFACE);
  eldbus_proxy_signal_handler_add(proxy, "Alive", _on_alive, NULL);
  eldbus_proxy_signal_handler_add(proxy, "Hello", _on_hello, NULL);

  c->proxy = proxy;

  /*
  eldbus_proxy_call(proxy, "SendBool", _on_send_bool, NULL, -1, "b",
                    expected.b);
  eldbus_proxy_call(proxy, "SendByte", _on_send_byte, NULL, -1, "y",
        expected.y);
  eldbus_proxy_call(proxy, "SendUint32", _on_send_uint32, NULL, -1, "u",
        expected.u);
  eldbus_proxy_call(proxy, "SendInt32", _on_send_int32, NULL, -1, "i",
        expected.i);
  eldbus_proxy_call(proxy, "SendInt16", _on_send_int16, NULL, -1, "n",
        expected.n);
  eldbus_proxy_call(proxy, "SendDouble", _on_send_double, NULL, -1, "d",
        expected.d);
  eldbus_proxy_call(proxy, "SendString", _on_send_string, NULL, -1, "s",
        expected.s);
  eldbus_proxy_call(proxy, "AsyncTest", _on_async_test, NULL, -1, "");
  eldbus_name_owner_changed_callback_add(conn, BUS, on_name_owner_changed,
        conn, EINA_TRUE);
  timeout = ecore_timer_add(30, finish, NULL);
  */
  //ecore_main_loop_begin();
}


InpaIMContext *
ecore_imf_context_inpa_new(void)
{
   EINA_LOG_DBG("%s", __FUNCTION__);


   InpaIMContext *context = calloc(1, sizeof(InpaIMContext));
   printf("newwewewewewewe\n");

   /* init bus object */
   /*
   if (_bus == NULL)
     {
        char *display_name = NULL;

        if ((display_name = getenv("DISPLAY")))
          ibus_set_display(display_name);
        else
          ibus_set_display(":0.0");

        _bus = ibus_bus_new();
     }
     */

   _init_dbus(context);

   return context;
}

EAPI void
ecore_imf_context_inpa_add(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa addddd \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);

   inpaimcontext->client_window = 0;

   // Init preedit status
   inpaimcontext->preedit_string = NULL;
   inpaimcontext->preedit_attrs = NULL;
   inpaimcontext->preedit_cursor_pos = 0;
   inpaimcontext->preedit_visible = EINA_FALSE;

   // Init cursor area
   inpaimcontext->cursor_x = -1;
   inpaimcontext->cursor_y = -1;
   inpaimcontext->cursor_w = 0;
   inpaimcontext->cursor_h = 0;

    inpaimcontext->has_focus = EINA_FALSE;
   inpaimcontext->ctx = ctx;

}

EAPI void
ecore_imf_context_inpa_del(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);

   InpaIMContext *inpaimcontext = (InpaIMContext*)ecore_imf_context_data_get(ctx);

   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

static void
_on_send_bool(void *data EINA_UNUSED, const Eldbus_Message *msg, Eldbus_Pending *pending EINA_UNUSED)
{
   const char *errname, *errmsg;
   Eina_Bool b;
   if (eldbus_message_error_get(msg, &errname, &errmsg))
     {
        ERR("%s %s", errname, errmsg);
        return;
     }
   if (!eldbus_message_arguments_get(msg, "b", &b))
     {
        ERR("Could not get entry contents");
        return;
     }
   if (b != EINA_TRUE)
     {
        ERR("Bool value doesn't match");
        return;
     }
   printf("bool send\n");
   //test();
}



EAPI void
inpa_show(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa_show \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

EAPI void
inpa_hide(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa_hide \n\n");


   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

EAPI void
inpa_focus_in(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("FOCUS inpa_focus_in \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);

  eldbus_proxy_call(inpaimcontext->proxy, "SendBool", _on_send_bool, NULL, -1, "b",
                    EINA_TRUE);
}

EAPI void
inpa_focus_out(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa_focus_out \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

EAPI void
inpa_control_show(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa_control_show \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

EAPI void
inpa_control_hide(Ecore_IMF_Context *ctx)
{
   EINA_LOG_DBG("%s", __FUNCTION__);
   printf("inpa_control_hide \n\n");

   InpaIMContext *inpaimcontext = (InpaIMContext *)ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(inpaimcontext);
}

