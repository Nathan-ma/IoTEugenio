#ifndef MACROS_DEBUG_H
#define MACROS_DEBUG_H

#undef ESP_LOGD
#undef ESP_LOGE
#undef ESP_LOGW
#undef ESP_LOGI
#undef log_e
#undef log_w
#undef log_i
#undef log_d
#undef LOG_FORMAT
#undef LOG_BOLD
#undef LOG_COLOR_V
#undef LOG_COLOR_W
#undef LOG_COLOR_D

#define LOG_LEVEL_NONE (0)
#define LOG_LEVEL_ERROR (1)
#define LOG_LEVEL_WARN (2)
#define LOG_LEVEL_INFO (3)
#define LOG_LEVEL_DEBUG (4)
#define LOG_LEVEL_VERBOSE (5)


#if CONFIG_LOG_COLORS
//#define LOG_COLOR_BLACK "30"
#define LOG_COLOR_RED "31"     //ERROR
#define LOG_COLOR_GREEN "32"   //INFO
#define LOG_COLOR_YELLOW "33"  //WARNING
//#define LOG_COLOR_BLUE "34"
//#define LOG_COLOR_MAGENTA "35"
#define LOG_COLOR_CYAN "36"  //DEBUG
#define LOG_COLOR_GRAY "37"  //VERBOSE
//#define LOG_COLOR_WHITE "38"

#define LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR) "\033[1;" COLOR "m"
#define LOG_RESET_COLOR "\033[0m"

#define LOG_COLOR_E LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W LOG_COLOR(LOG_COLOR_YELLOW)
#define LOG_COLOR_I LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D LOG_COLOR(LOG_COLOR_CYAN)
#define LOG_COLOR_V LOG_COLOR(LOG_COLOR_GRAY)
#else
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif

#define LOG_FORMAT(tag, letter, format) LOG_COLOR_##letter "[" #letter "] [%s] %s(): " format LOG_RESET_COLOR "\r\n", tag, __FUNCTION__
#define LOG_N_FORMAT(tag, letter, format) LOG_COLOR_##letter "[%s] " format LOG_RESET_COLOR "\r\n", tag

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define log_d(tag, format, ...) printf(LOG_N_FORMAT(tag, D, format), ##__VA_ARGS__)
#else
#define log_d(tag, format, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define log_i(tag, format, ...) printf(LOG_N_FORMAT(tag, I, format), ##__VA_ARGS__)
#else
#define log_i(tag, format, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define log_w(tag, format, ...) printf(LOG_FORMAT(tag, W, format), ##__VA_ARGS__)
#else
#define log_w(tag, format, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define log_e(tag, format, ...) printf(LOG_FORMAT(tag, E, format), ##__VA_ARGS__)
#else
#define log_e(tag, format, ...)
#endif

#ifdef DEBUG_ESP_PORT
#define ESP_LOGE(tag, ...) 
#define ESP_LOGW(tag, ...) 
#define ESP_LOGI(tag, ...) 
#define ESP_LOGD(tag, ...) 
#else
#define ESP_LOGI(tag, ...) log_i(tag, __VA_ARGS__)
#define ESP_LOGW(tag, ...) log_w(tag, __VA_ARGS__)
#define ESP_LOGE(tag, ...) log_e(tag, __VA_ARGS__)
#define ESP_LOGD(tag, ...) log_d(tag, __VA_ARGS__)
#endif

#endif
