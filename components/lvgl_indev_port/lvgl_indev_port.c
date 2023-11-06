#include "lvgl_indev_port.h"

#define TAG "ESP"

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

lv_indev_t *indev_encoder;
lv_group_t *group;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);

    group = lv_group_create();
    lv_indev_set_group(indev_encoder, group);
}

static void encoder_init(void)
{
    encoder_config();
}

static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static int32_t last_cnt; /* 编码器上一次计数值 */
    int32_t dir = 0;
    int32_t cnt = encoder_get_diff();
    /* 方向判断 */
    if (cnt - last_cnt < 0 && cnt - last_cnt <= -1)
    {
        dir = -1; /* 逆时针旋转 */
    }
    else if (cnt - last_cnt > 0 && cnt - last_cnt >= 1)
    {
        dir = 1; /* 顺时针旋转 */
    }
    last_cnt = cnt;
    static bool last_state;

    data->enc_diff = dir;

    int enc_diff = dir;

    // ESP_LOGI("ESP", "enc_diff = %d\n", enc_diff);

    bool is_push = encoder_get_is_push();
    data->state = is_push ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

    if (is_push != last_state)
    {
        last_state = is_push;
    }
}

lv_indev_t *get_indev(void)
{
    return indev_encoder;
}

lv_group_t *get_group(void)
{
    return group;
}