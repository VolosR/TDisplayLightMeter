/**
 * @file      LV_Helper.cpp
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-09-22
 *
 */

#include "LV_Helper.h"
//#include "utilities.h"
#include <TFT_eSPI.h>



TFT_eSPI tft = TFT_eSPI();


#define BOARD_TFT_WIDTH     170 
#define BOARD_TFT_HEIHT     320


static void lv_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                          lv_color_t *color_p)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, false );
    tft.endWrite();
    lv_disp_flush_ready( disp );
}

static void lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

}









void lv_helper(uint8_t r)
{
    static lv_color_t *frameBuffer;
    static lv_disp_drv_t disp_drv;
    static lv_disp_draw_buf_t draw_buf;




    // Init Display
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);



    lv_init();

    size_t buffer_size = sizeof(lv_color_t) * tft.width() * tft.height();
    frameBuffer  = (lv_color_t *)ps_malloc(buffer_size);
    assert(frameBuffer);

    lv_disp_drv_init(&disp_drv);
    lv_disp_draw_buf_init(&draw_buf, frameBuffer, NULL, buffer_size);

    disp_drv.hor_res = tft.width();
    disp_drv.ver_res = tft.height();
    disp_drv.flush_cb = lv_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_touchpad_read;
    lv_indev_drv_register(&indev_drv);

}



























