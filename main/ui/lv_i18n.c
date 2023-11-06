#include "./lv_i18n.h"


////////////////////////////////////////////////////////////////////////////////
// Define plural operands
// http://unicode.org/reports/tr35/tr35-numbers.html#Operands

// Integer version, simplified

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static uint8_t en_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_lang = {
    .locale_name = "en",


    .locale_plural_fn = en_plural_fn
};

static lv_i18n_phrase_t es_singulars[] = {
    {"Scroll to choose menu, Press to Start", "Desplazar para elegir menú, Presionar para iniciar"},
    {"Temp", "Temp"},
    {"Countdown", "Cuenta regresiva"},
    {"Heat", "Calentar"},
    {"Set Temp", "Configurar temp"},
    {"Press to Start", "Presionar para iniciar"},
    {"Set Countdown", "Configurar cuenta regresiva"},
    {"User Menu: Create", "Crear menú de usuario"},
    {"Choose Menu", "Elegir menú"},
    {"User Menu: Delete", "Borrar menú de usuario"},
    {"User Menu: Edit | Spec", "Editar menú de usuario | Especificaciones"},
    {"User Menu: Edit | Select menu", "Editar menú de usuario | Seleccionar menú"},
    {"User Menu: Create | Edit | Delete", "Crear | Editar | Borrar menú de usuario"},
    {"Create\\nMenu", "Crear\\nmenú"},
    {"Edit\\nMenu", "Editar\\nmenú"},
    {"Delete\\nMenu", "Borrar\\nmenú"},
    {"Settings", "Configuración"},
    {"Self Clean (min)", "Autolimpieza (min)"},
    {"Power Mode", "Modo de potencia"},
    {"Language", "Idioma"},
    {"Menu", "Menú"},
    {"About", "Acerca de"},
    {"Reset", "Restablecer"},
    {"Temperature Calibration", "Calibración de temperatura"},
    {"Unit", "Unidad"},
    {"Demo Mode", "Modo demostración"},
    {"Hi Limit Cut-OFF", "Corte por límite alto"},
    {"Touch Screen", "Pantalla táctil"},
    {"Continuous Heat", "Funcionamiento continuo"},
    {"Abnormal temperature. Rebooting.", "Temperatura anormal, reiniciando."},
    {"Heat pipe lifting", "Tubo del calentador levantado"},
    {"Draining. Please Wait.", "Por favor, espere mientras se drena el aceite."},
    {"Press Start to turn on cooking.", "Pulse para iniciar la cocción"},
    // {"Manual Operation", "modo manual"},
    {"Manual Operation", "Manual Operation"},
    {"Drop Food", "Gota de comida"},
    {NULL, NULL} // End mark
};



static uint8_t es_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);


    if ((n == 1)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t es_lang = {
    .locale_name = "es",
    .singulars = es_singulars,

    .locale_plural_fn = es_plural_fn
};

static lv_i18n_phrase_t fr_singulars[] = {
    {"Scroll to choose menu, Press to Start", "Défilez pour choisir le menu, Appuyez pour démarrer"},
    {"Temp", "Temp."},
    {"Countdown", "Compte à rebours"},
    {"Heat", "Chauffe"},
    {"Set Temp", "Réglage temp."},
    {"Press to Start", "Appuyez pour démarrer"},
    {"Set Countdown", "Réglage compte à rebours"},
    {"User Menu: Create", "Menu utilisateur : Créer"},
    {"Choose Menu", "Choisissez un menu"},
    {"User Menu: Delete", "Menu utilisateur : Supprimer"},
    {"User Menu: Edit | Spec", "Menu utilisateur : Modifier | Spécification"},
    {"User Menu: Edit | Select menu", "Menu utilisateur : Modifier | Sélectionner menu"},
    {"User Menu: Create | Edit | Delete", "Menu utilisateur : Créer | Modifier | Supprimer"},
    {"Create\\nMenu", "Créer\\nMenu"},
    {"Edit\\nMenu", "Modifier\\nMenu"},
    {"Delete\\nMenu", "Supprimer\\nMenu"},
    {"Settings", "Paramètres"},
    {"Self Clean (min)", "Nettoyage automatique (min)"},
    {"Power Mode", "Mode de puissance"},
    {"Language", "Langue"},
    {"Menu", "Menu"},
    {"About", "À propos"},
    {"Reset", "Réinitialiser"},
    {"Temperature Calibration", "Calibration température"},
    {"Unit", "Unité"},
    {"Demo Mode", "Mode démo"},
    {"Hi Limit Cut-OFF", "Coupure limite haute"},
    {"Touch Screen", "Écran tactile"},
    {"Continuous Heat", "Fonctionnement continu"},
    {"Abnormal temperature. Rebooting.", "Température anormale, redémarrage."},
    {"Heat pipe lifting", "Tube de chauffage soulevé"},
    {"Draining. Please Wait.", "Veuillez patienter pendant la vidange de l'huile."},
    {"Press Start to turn on cooking.", "Appuyer pour démarrer la cuisson"},
    // {"Manual Operation", "mode manuel"},
    {"Manual Operation", "Manual Operation"},
    {"Drop Food", "laisser tomber la nourriture"},
    {NULL, NULL} // End mark
};



static uint8_t fr_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);

    if ((((i == 0) || (i == 1)))) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t fr_lang = {
    .locale_name = "fr",
    .singulars = fr_singulars,

    .locale_plural_fn = fr_plural_fn
};

static lv_i18n_phrase_t id_singulars[] = {
    {"Scroll to choose menu, Press to Start", "Gulir untuk memilih menu, Tekan untuk Memulai"},
    {"Temp", "Suhu"},
    {"Countdown", "Mundur"},
    {"Heat", "Heat"},
    {"Set Temp", "Atur Suhu"},
    {"Press to Start", "Tekan untuk Memulai"},
    {"Set Countdown", "Atur Mundur"},
    {"User Menu: Create", "Buat Menu Pengguna"},
    {"Choose Menu", "Pilih Menu"},
    {"User Menu: Delete", "Hapus Menu Pengguna"},
    {"User Menu: Edit | Spec", "Edit Menu Pengguna | Spesifikasi"},
    {"User Menu: Edit | Select menu", "Edit Menu Pengguna | Pilih menu"},
    {"User Menu: Create | Edit | Delete", "Buat | Edit | Hapus Menu Pengguna"},
    {"Create\\nMenu", "Buat\\nMenu"},
    {"Edit\\nMenu", "Edit\\nMenu"},
    {"Delete\\nMenu", "Hapus\\nMenu"},
    {"Settings", "Pengaturan"},
    {"Self Clean (min)", "Pembersihan Otomatis (mnt)"},
    {"Power Mode", "Mode Pemanasan"},
    {"Language", "Bahasa"},
    {"Menu", "Menu"},
    {"About", "Tentang"},
    {"Reset", "Reset"},
    {"Temperature Calibration", "Kalibrasi Suhu"},
    {"Unit", "Unit"},
    {"Demo Mode", "Mode Demo"},
    {"Hi Limit Cut-OFF", "Batas Atas Putus"},
    {"Touch Screen", "Layar Sentuh"},
    {"Continuous Heat", "Continuous Heat"},
    {"Abnormal temperature. Rebooting.", "Suhu tidak normal. Sedang Merestart."},
    {"Heat pipe lifting", "Pipa pemanas terangkat"},
    {"Draining. Please wait.", "Sedang Menguras. Mohon tunggu."},
    {"Press Start to turn on cooking.", "Tekan Mulai untuk mengaktifkan memasak."},
    {"Manual Operation", "Operasi Manual"},
    {"Drop Food", "Letakkan Makanan"},
    {"Press anywhere or any button to exit", "Press anywhere or any button to exit"},
    {"Done", "Selesai"},
    {NULL, NULL} // End mark
};



static uint8_t id_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t id_lang = {
    .locale_name = "id",
    .singulars = id_singulars,

    .locale_plural_fn = id_plural_fn
};

static lv_i18n_phrase_t zh_cn_singulars[] = {
    {"Scroll to choose menu, Press to Start", "滚动选择菜单，按下开始"},
    {"Temp", "温度"},
    {"Countdown", "倒计时"},
    {"Heat", "预热中"},
    {"Set Temp", "设定温度"},
    {"Press to Start", "按下开始"},
    {"Set Countdown", "设定倒计时"},
    {"User Menu: Create", "创建用户菜单"},
    {"Choose Menu", "选择菜单"},
    {"User Menu: Delete", "删除用户菜单"},
    {"User Menu: Edit | Spec", "编辑用户菜单 | 规格"},
    {"User Menu: Edit | Select menu", "编辑用户菜单 | 选择菜单"},
    {"User Menu: Create | Edit | Delete", "创建 | 编辑 | 删除用户菜单"},
    {"Create\\nMenu", "新增菜单"},
    {"Edit\\nMenu", "编辑菜单"},
    {"Delete\\nMenu", "删除菜单"},
    {"Settings", "设置"},
    {"Self Clean (min)", "自清洁（分钟）"},
    {"Power Mode", "加热模式"},
    {"Language", "语言"},
    {"Menu", "菜单"},
    {"About", "关于"},
    {"Reset", "重置"},
    {"Temperature Calibration", "温度校准"},
    {"Unit", "单位"},
    {"Demo Mode", "演示模式"},
    {"Hi Limit Cut-OFF", "高温断电"},
    {"Touch Screen", "触摸屏"},
    {"Continuous Heat", "持续运行"},
    {"Abnormal temperature. Rebooting.", "温度异常，正在重启"},
    {"Heat pipe lifting", "发热管抬起"},
    {"Draining. Please Wait.", "正在泄油，请稍等"},
    {"Press Start to turn on cooking.", "按下开始开启烹饪"},
    // {"Manual Operation", "手动模式"},
    {"Manual Operation", "Manual Operation"},
    {"Drop Food", "投放食物"},
    {NULL, NULL} // End mark
};



static uint8_t zh_cn_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
    .locale_name = "zh-cn",
    .singulars = zh_cn_singulars,

    .locale_plural_fn = zh_cn_plural_fn
};

static lv_i18n_phrase_t zh_hk_singulars[] = {
    {"Scroll to choose menu, Press to Start", "滾動滾輪選擇菜單，按下啟動倒計時"},
    {"Temp", "溫度"},
    {"Countdown", "倒計時"},
    {"Heat", "預熱中"},
    {"Set Temp", "設定溫度"},
    {"Press to Start", "按下開始鍵啟動"},
    {"Set Countdown", "設定倒計時"},
    {"User Menu: Create", "用戶菜單：新增"},
    {"Choose Menu", "選擇菜單"},
    {"User Menu: Delete", "用戶菜單：刪除"},
    {"User Menu: Edit | Spec", "用戶菜單：編輯 | 規格"},
    {"User Menu: Edit | Select menu", "用戶菜單：編輯 | 選擇菜單"},
    {"User Menu: Create | Edit | Delete", "用戶菜單：新增 | 編輯 | 刪除"},
    {"Create\\nMenu", "新增菜單"},
    {"Edit\\nMenu", "編輯菜單"},
    {"Delete\\nMenu", "刪除菜單"},
    {"Settings", "設置"},
    {"Self Clean (min)", "自清潔（分鐘）"},
    {"Power Mode", "加熱模式"},
    {"Language", "語言"},
    {"Menu", "菜單"},
    {"About", "關於"},
    {"Reset", "還原"},
    {"Temperature Calibration", "溫度校正"},
    {"Unit", "單位"},
    {"Demo Mode", "示範模式"},
    {"Hi Limit Cut-OFF", "超溫保護斷電"},
    {"Touch Screen", "觸摸屏"},
    {"Continuous Heat", "持續運轉"},
    {"Abnormal temperature. Rebooting.", "溫度異常，正在重啓"},
    {"Heat pipe lifting", "發熱管擡起"},
    {"Draining. Please Wait.", "正在泄油，請稍等"},
    {"Press Start to turn on cooking.", "按下開始開啓烹飪"},
    // {"Manual Operation", "手動模式"},
    {"Manual Operation", "Manual Operation"},
    {"Drop Food", "投放食物"},
    {NULL, NULL} // End mark
};



static uint8_t zh_hk_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_hk_lang = {
    .locale_name = "zh-hk",
    .singulars = zh_hk_singulars,

    .locale_plural_fn = zh_hk_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &en_lang,
    &es_lang,
    &fr_lang,
    &id_lang,
    &zh_cn_lang,
    &zh_hk_lang,
    NULL // End mark
};

////////////////////////////////////////////////////////////////////////////////


// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
 * Reset internal state. For testing.
 */
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
 * Set the languages for internationalization
 * @param langs pointer to the array of languages. (Last element has to be `NULL`)
 */
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
    if(langs == NULL) return -1;
    if(langs[0] == NULL) return -1;

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
 * Change the localization (language)
 * @param l_name name of the translation locale to use. E.g. "en-GB"
 */
int lv_i18n_set_locale(const char * l_name)
{
    if(current_lang_pack == NULL) return -1;

    uint16_t i;

    for(i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
    uint16_t i;
    for(i = 0; trans[i].msg_id != NULL; i++) {
        if(strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if(trans[i].translation) return trans[i].translation;
        }
    }

    return NULL;
}


/**
 * Get the translation from a message ID
 * @param msg_id message ID
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text(const char * msg_id)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;

    // Search in current locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    return msg_id;
}

/**
 * Get the translation from a message ID and apply the language's plural rule to get correct form
 * @param msg_id message ID
 * @param num an integer to select the correct plural form
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    return msg_id;
}

/**
 * Get the name of the currently used locale.
 * @return name of the currently used locale. E.g. "en-GB"
 */
const char * lv_i18n_get_current_locale(void)
{
    if(!current_lang) return NULL;
    return current_lang->locale_name;
}
