/**
 * @file ebs_config.h
 * @brief Electronic Braking System - Configuration Parameters
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * System configuration parameters and compile-time settings
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#ifndef EBS_CONFIG_H
#define EBS_CONFIG_H

/* System Configuration */
#define EBS_VERSION_MAJOR           1U
#define EBS_VERSION_MINOR           0U
#define EBS_VERSION_PATCH           0U
#define EBS_BUILD_NUMBER            1U

/* Hardware Configuration */
#define EBS_MCU_FREQUENCY_HZ        300000000U  /* 300 MHz */
#define EBS_SYSTEM_TICK_HZ          1000U       /* 1 kHz system tick */
#define EBS_CAN_BAUDRATE            500000U     /* 500 kbps */

/* Feature Configuration */
#define EBS_ENABLE_ABS              1U          /* Enable ABS function */
#define EBS_ENABLE_ESC              1U          /* Enable ESC function */
#define EBS_ENABLE_TCS              1U          /* Enable TCS function */
#define EBS_ENABLE_BRAKE_ASSIST     1U          /* Enable brake assist */
#define EBS_ENABLE_DIAGNOSTICS      1U          /* Enable diagnostics */
#define EBS_ENABLE_CYBERSECURITY    1U          /* Enable security features */

/* Safety Configuration */
#define EBS_SAFETY_DUAL_CHANNEL     1U          /* Enable dual-channel safety */
#define EBS_SAFETY_WATCHDOG         1U          /* Enable watchdog monitoring */
#define EBS_SAFETY_MEMORY_PROTECT   1U          /* Enable memory protection */
#define EBS_SAFETY_CRC_CHECK        1U          /* Enable CRC checking */

/* Debug Configuration */
#define EBS_DEBUG_ENABLED           1U          /* Enable debug features */
#define EBS_DEBUG_UART_ENABLED      1U          /* Enable UART debug output */
#define EBS_DEBUG_CAN_ENABLED       1U          /* Enable CAN debug messages */
#define EBS_DEBUG_TRACE_ENABLED     0U          /* Enable execution tracing */

/* Memory Configuration */
#define EBS_STACK_SIZE_MAIN         (8U * 1024U)    /* Main task stack size */
#define EBS_STACK_SIZE_SAFETY       (4U * 1024U)    /* Safety task stack size */
#define EBS_STACK_SIZE_ISR          (2U * 1024U)    /* ISR stack size */
#define EBS_HEAP_SIZE               (64U * 1024U)   /* Heap size */

/* Task Configuration */
#define EBS_TASK_PRIORITY_SAFETY    255U        /* Highest priority */
#define EBS_TASK_PRIORITY_ABS       200U        /* High priority */
#define EBS_TASK_PRIORITY_ESC       190U        /* High priority */
#define EBS_TASK_PRIORITY_TCS       180U        /* Medium-high priority */
#define EBS_TASK_PRIORITY_COMM      100U        /* Medium priority */
#define EBS_TASK_PRIORITY_DIAG      50U         /* Low priority */

/* Timing Configuration */
#define EBS_CYCLE_TIME_SAFETY_MS    1U          /* Safety task cycle time */
#define EBS_CYCLE_TIME_ABS_MS       1U          /* ABS task cycle time */
#define EBS_CYCLE_TIME_ESC_MS       5U          /* ESC task cycle time */
#define EBS_CYCLE_TIME_TCS_MS       10U         /* TCS task cycle time */
#define EBS_CYCLE_TIME_COMM_MS      10U         /* Communication cycle time */
#define EBS_CYCLE_TIME_DIAG_MS      100U        /* Diagnostic cycle time */

/* Sensor Configuration */
#define EBS_WHEEL_SPEED_SENSORS     4U          /* Number of wheel speed sensors */
#define EBS_PRESSURE_SENSORS        6U          /* Number of pressure sensors */
#define EBS_SENSOR_TIMEOUT_MS       50U         /* Sensor data timeout */
#define EBS_SENSOR_FILTER_ALPHA     0.1f        /* Low-pass filter coefficient */

/* Actuator Configuration */
#define EBS_HYDRAULIC_VALVES        8U          /* Number of hydraulic valves */
#define EBS_PWM_FREQUENCY_HZ        1000U       /* PWM frequency for valves */
#define EBS_PWM_RESOLUTION_BITS     16U         /* PWM resolution */
#define EBS_VALVE_RESPONSE_TIME_MS  10U         /* Valve response time */

/* Algorithm Configuration */
#define EBS_ABS_SLIP_THRESHOLD      0.15f       /* ABS slip threshold */
#define EBS_ABS_SLIP_TARGET         0.10f       /* ABS target slip */
#define EBS_ABS_PRESSURE_STEP       0.1f        /* ABS pressure step size */
#define EBS_ABS_CYCLE_FREQ_MIN      4.0f        /* Minimum ABS cycle frequency */
#define EBS_ABS_CYCLE_FREQ_MAX      20.0f       /* Maximum ABS cycle frequency */

#define EBS_ESC_YAW_THRESHOLD       5.0f        /* ESC yaw rate threshold */
#define EBS_ESC_LATERAL_THRESHOLD   8.0f        /* ESC lateral acceleration threshold */
#define EBS_ESC_KP                  1000.0f     /* ESC proportional gain */
#define EBS_ESC_KI                  500.0f      /* ESC integral gain */
#define EBS_ESC_KD                  100.0f      /* ESC derivative gain */

#define EBS_TCS_SLIP_THRESHOLD      0.10f       /* TCS slip threshold */
#define EBS_TCS_SLIP_TARGET         0.05f       /* TCS target slip */
#define EBS_TCS_TORQUE_REDUCTION    50.0f       /* Maximum torque reduction % */

/* Communication Configuration */
#define EBS_CAN_TX_BUFFER_SIZE      32U         /* CAN TX buffer size */
#define EBS_CAN_RX_BUFFER_SIZE      64U         /* CAN RX buffer size */
#define EBS_CAN_TIMEOUT_MS          100U        /* CAN timeout */
#define EBS_CAN_RETRY_COUNT         3U          /* CAN retry count */

/* Diagnostic Configuration */
#define EBS_DTC_BUFFER_SIZE         50U         /* DTC buffer size */
#define EBS_EVENT_LOG_SIZE          100U        /* Event log size */
#define EBS_FREEZE_FRAME_SIZE       32U         /* Freeze frame data size */
#define EBS_DTC_AGING_CYCLES        40U         /* DTC aging cycles */

/* Security Configuration */
#define EBS_CRYPTO_KEY_SIZE         32U         /* Cryptographic key size (256-bit) */
#define EBS_CRYPTO_BLOCK_SIZE       16U         /* AES block size */
#define EBS_CRYPTO_MAC_SIZE         32U         /* MAC size (256-bit) */
#define EBS_CRYPTO_NONCE_SIZE       16U         /* Nonce size */
#define EBS_AUTH_TIMEOUT_MS         5000U       /* Authentication timeout */
#define EBS_SESSION_TIMEOUT_MS      300000U     /* Session timeout (5 minutes) */

/* Hardware Abstraction Layer Configuration */
#define EBS_HAL_ADC_CHANNELS        16U         /* Number of ADC channels */
#define EBS_HAL_PWM_CHANNELS        12U         /* Number of PWM channels */
#define EBS_HAL_GPIO_INPUTS         24U         /* Number of GPIO inputs */
#define EBS_HAL_GPIO_OUTPUTS        16U         /* Number of GPIO outputs */
#define EBS_HAL_CAN_INTERFACES      3U          /* Number of CAN interfaces */
#define EBS_HAL_SPI_INTERFACES      2U          /* Number of SPI interfaces */

/* Calibration Parameters */
#define EBS_CAL_WHEEL_CIRCUMFERENCE 2.0f        /* Wheel circumference in meters */
#define EBS_CAL_WHEELBASE           2.7f        /* Vehicle wheelbase in meters */
#define EBS_CAL_TRACK_WIDTH_FRONT   1.6f        /* Front track width in meters */
#define EBS_CAL_TRACK_WIDTH_REAR    1.6f        /* Rear track width in meters */
#define EBS_CAL_VEHICLE_MASS        1500.0f     /* Vehicle mass in kg */
#define EBS_CAL_UNDERSTEER_GRAD     0.002f      /* Understeer gradient */

/* Environmental Limits */
#define EBS_TEMP_MIN_CELSIUS        -40         /* Minimum operating temperature */
#define EBS_TEMP_MAX_CELSIUS        85          /* Maximum operating temperature */
#define EBS_VOLTAGE_MIN_V           9.0f        /* Minimum supply voltage */
#define EBS_VOLTAGE_MAX_V           16.0f       /* Maximum supply voltage */
#define EBS_VOLTAGE_NOMINAL_V       12.0f       /* Nominal supply voltage */

/* Test Configuration */
#define EBS_TEST_MODE_ENABLED       0U          /* Enable test mode */
#define EBS_HIL_MODE_ENABLED        0U          /* Enable HIL mode */
#define EBS_SIMULATION_MODE         0U          /* Enable simulation mode */
#define EBS_BENCH_TEST_MODE         0U          /* Enable bench test mode */

/* Compiler and Platform Configuration */
#ifdef __GNUC__
    #define EBS_COMPILER_GCC        1U
    #define EBS_INLINE              inline
    #define EBS_FORCE_INLINE        __attribute__((always_inline)) inline
    #define EBS_NO_RETURN           __attribute__((noreturn))
    #define EBS_PACKED              __attribute__((packed))
    #define EBS_ALIGNED(x)          __attribute__((aligned(x)))
#elif defined(__ICCARM__)
    #define EBS_COMPILER_IAR        1U
    #define EBS_INLINE              inline
    #define EBS_FORCE_INLINE        _Pragma("inline=forced")
    #define EBS_NO_RETURN           __noreturn
    #define EBS_PACKED              __packed
    #define EBS_ALIGNED(x)          _Pragma("data_alignment=" #x)
#else
    #define EBS_COMPILER_UNKNOWN    1U
    #define EBS_INLINE              
    #define EBS_FORCE_INLINE        
    #define EBS_NO_RETURN           
    #define EBS_PACKED              
    #define EBS_ALIGNED(x)          
#endif

/* Assert Configuration */
#if EBS_DEBUG_ENABLED
    #define EBS_ASSERT(expr)        do { if (!(expr)) EBS_AssertFailed(__FILE__, __LINE__); } while(0)
    #define EBS_ASSERT_PARAM(expr)  EBS_ASSERT(expr)
#else
    #define EBS_ASSERT(expr)        ((void)0)
    #define EBS_ASSERT_PARAM(expr)  ((void)0)
#endif

/* Static Analysis Configuration */
#define EBS_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)

/* Memory Barriers */
#define EBS_MEMORY_BARRIER()        __asm__ volatile ("" ::: "memory")
#define EBS_COMPILER_BARRIER()      __asm__ volatile ("" ::: "memory")

/* Critical Section Macros */
#define EBS_ENTER_CRITICAL()        __disable_irq()
#define EBS_EXIT_CRITICAL()         __enable_irq()

/* Unused Parameter Macro */
#define EBS_UNUSED(x)               ((void)(x))

/* Array Size Macro */
#define EBS_ARRAY_SIZE(arr)         (sizeof(arr) / sizeof((arr)[0]))

/* Min/Max Macros */
#define EBS_MIN(a, b)               (((a) < (b)) ? (a) : (b))
#define EBS_MAX(a, b)               (((a) > (b)) ? (a) : (b))
#define EBS_CLAMP(val, min, max)    EBS_MAX(min, EBS_MIN(val, max))

/* Bit Manipulation Macros */
#define EBS_BIT(n)                  (1U << (n))
#define EBS_SET_BIT(reg, bit)       ((reg) |= EBS_BIT(bit))
#define EBS_CLEAR_BIT(reg, bit)     ((reg) &= ~EBS_BIT(bit))
#define EBS_TOGGLE_BIT(reg, bit)    ((reg) ^= EBS_BIT(bit))
#define EBS_TEST_BIT(reg, bit)      (((reg) & EBS_BIT(bit)) != 0U)

/* Function Prototypes for Configuration */
void EBS_AssertFailed(const char* file, uint32_t line);
void EBS_Delay_Ms(uint32_t delay_ms);
void EBS_Delay_Us(uint32_t delay_us);

#endif /* EBS_CONFIG_H */
