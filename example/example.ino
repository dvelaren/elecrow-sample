// Librerias
#include <PCA9557.h>
#include <SPI.h>
#include <Wire.h>
#include <lvgl.h>

#include "gfx_conf.h"  // Config de la pantalla
#include "ui.h"

// Etiquetado de pines
#define TFT_BL_PIN 2      // Pin de retroiluminación de la pantalla TFT
#define I2C_SDA_PIN 19    // Pin SDA para I2C
#define I2C_SCL_PIN 20    // Pin SCL para I2C
#define I2S_SDIN_PIN 17   // Pin SDIN para I2S
#define I2S_LRCLK_PIN 18  // Pin LRCLK para I2S
#define I2S_BCLK_PIN 42   // Pin BCLK para I2S
#define GPIO_D_PIN 38     // Pin GPIO disponible

// Constantes
#define DEFAULT_BRIGHTNESS 255  // Brillo por defecto
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf1[screenWidth * screenHeight / 10];
static lv_color_t disp_draw_buf2[screenWidth * screenHeight / 10];
static lv_disp_drv_t disp_drv;

// Variables
PCA9557 Out;  // for touch timing init

// Subrutinas y funciones
/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;

    // Serial.print( "Data x " );
    // Serial.println( touchX );

    // Serial.print( "Data y " );
    // Serial.println( touchY );
  }
}

void setup() {
  // 1. Config de pines
  pinMode(GPIO_D_PIN, OUTPUT);
  pinMode(I2S_SDIN_PIN, OUTPUT);
  pinMode(I2S_LRCLK_PIN, OUTPUT);
  pinMode(I2S_BCLK_PIN, OUTPUT);
  pinMode(TFT_BL_PIN, OUTPUT);

  // 2. Limpieza de salidas
  digitalWrite(GPIO_D_PIN, LOW);
  digitalWrite(I2S_SDIN_PIN, LOW);
  digitalWrite(I2S_LRCLK_PIN, LOW);
  digitalWrite(I2S_BCLK_PIN, LOW);
  analogWrite(TFT_BL_PIN, DEFAULT_BRIGHTNESS);

  // 3. Comunicaciones
  Serial.begin(115200);

  // touch timing init
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Out.reset();
  Out.setMode(IO_OUTPUT);
  Out.setState(IO0, IO_LOW);
  Out.setState(IO1, IO_LOW);
  delay(20);
  Out.setState(IO0, IO_HIGH);
  delay(100);
  Out.setMode(IO1, IO_INPUT);

  // Display Prepare
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  delay(200);

  lv_init();

  delay(100);

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, screenWidth * screenHeight / 10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.full_refresh = 1;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  tft.fillScreen(TFT_BLACK);

  ui_init();
}

void loop() {
  lv_timer_handler();
  delay(5);
}
