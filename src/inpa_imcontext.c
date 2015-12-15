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

   //int              caps;
};

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

