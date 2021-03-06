/**
  ******************************************************************************
  * @file    adc.h
  * @author  YANDLD
  * @version V2.5
  * @date    2014.3.25
  * @brief   www.beyondcore.net   http://upcmcu.taobao.com 
  * @note    此文件为芯片ADC模块的底层功能函数
  ******************************************************************************
  */
#ifndef __CH_LIB_ADC_H__
#define __CH_LIB_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

//!< ADC外设模块号
#define HW_ADC0  (0) //ADC0模块
#define HW_ADC1  (1) //ADC1模块
#define HW_ADC2  (2) //ADC2模块


//!< ADC 快速初始化宏
#define ADC0_SE0_DP0        (0x0U)      /* ADC0模块的0通道，DP0引脚 */
#define ADC0_SE1_DP1        (0x80000U)  
#define ADC0_SE3_DP3        (0x180000U) 
#define ADC0_SE4B_PC2       (0x204410U) /* ADC0模块的4B通道，PC2引脚  使用B通道时，需要设置 ADC_ChlMuxConfig */ 
#define ADC0_SE5B_PD1       (0x284218U) 
#define ADC0_SE6B_PD5       (0x304a18U)
#define ADC0_SE7B_PD6       (0x384c18U)
#define ADC0_SE8_PB0        (0x404008U)
#define ADC0_SE9_PB1        (0x484208U)
#define ADC0_SE12_PB2       (0x604408U)
#define ADC0_SE13_PB3       (0x684608U)
#define ADC0_SE14_PC0       (0x704010U)
#define ADC0_SE15_PC1       (0x784010U)
#define ADC0_SE17_E24       (0x887020U)
#define ADC0_SE18_E25       (0x907220U)
#define ADC0_SE19_DM0       (0x980000U)
#define ADC0_SE20_DM1       (0xa00000U)
#define ADC0_SE26_TEMP      (0xd00000U)
#define ADC1_SE0_DP0        (0x1U)
#define ADC1_SE1_DP1        (0x80001U)
#define ADC1_SE3_DP3        (0x180001U)
#define ADC1_SE4_PE0        (0x204021U)
#define ADC1_SE5_PE1        (0x284221U)
#define ADC1_SE6_PE2        (0x304421U)
#define ADC1_SE7_PE3        (0x384621U)
#define ADC1_SE4B_PC8       (0x205011U)
#define ADC1_SE5B_PC9       (0x285211U)
#define ADC1_SE6B_PC10      (0x305411U)
#define ADC1_SE7B_PC11      (0x385611U)
#define ADC1_SE8_PB0        (0x404009U)
#define ADC1_SE9_PB1        (0x484209U)
#define ADC1_SE14_PB10      (0x705409U)
#define ADC1_SE15_PB11      (0x785609U)
#define ADC1_SE17_PA17      (0x886201U)
#define ADC1_SE19_DM0       (0x980001U)
#define ADC1_SE20_DM1       (0xa00001U)
#define ADC1_SE26_TEMP      (0xd00001U)
#define ADC0_SE21           (0x00B00000) /* analog pin */
#define ADC0_SE22           (0x00B00000)
#define ADC1_SE16           (0x00800001)
#define ADC1_SE18           (0x00900001)
#define ADC0_SE23           (0x00B80000)
#define ADC1_SE23           (0x00B80001)

//!< ADC 转换时钟分频因子,控制转换速度
typedef enum
{
    kADC_ClockDiv1,  
    kADC_ClockDiv2,
    kADC_ClockDiv4,
    kADC_ClockDiv8,
}ADC_ClockDiv_Type;

//!< ADC转换精度定义
typedef enum
{
    kADC_SingleDiff8or9 = 0,    /* 单端8位或 差分9位精度 */
    kADC_SingleDiff12or13 = 1,  /* 单端12位或 差分13位精度 */
    kADC_SingleDiff10or11 = 2,  
    kADC_SingleDIff16 = 3,
}ADC_ResolutionMode_Type;

//!< ADC 触发方式定义
typedef enum
{
    kADC_TriggerSoftware,  //软件触发
    kADC_TriggerHardware,  //硬件触发
}ADC_TriggerSelect_Type;

//!< 是否连续转换
typedef enum
{
    kADC_ContinueConversionEnable,   //开启连续转换
    kADC_ContinueConversionDisable,  //关闭连续转换
}ADC_ContinueMode_Type;

//!< 单端ADC还是查分ADC
typedef enum
{
    kADC_Single,         //单端模式
    kADC_Differential,   //差分模式
}ADC_SingleOrDiffMode_Type;

//!< ADC 通道触发器复用选择(每个ADC通道有2个ADC转换触发器 为MuxA 和 MuxB. MuxB 只能硬件触发)
#define kADC_MuxA                (0x00)
#define kADC_MuxB                (0x01)
//!< ADC 通道复用选择(SEA 还是SEB) 硬件通道选择
#define kADC_ChlMuxA             (0x00)
#define kADC_ChlMuxB             (0x01)

//!< 模拟电压参考源
typedef enum
{
    kADC_VoltageVREF,  /* 使用外部引脚VREFH VREFL 作为参考电源 */
    kADC_VoltageVALT,  /* 可选的第二电压参考源 不同的型号可能连接到不同的模块上 K60DN512Vxxx 连接到 VREF模块 */
}ADC_VoltageRef_Type;

//!< 硬件平均
typedef enum
{
    kADC_HardwareAverageDisable,  //关闭硬件平均
    kADC_HardwareAverage_4,       //4均值
    kADC_HardwareAverage_8,       //8均值
    kADC_HardwareAverage_16,
    kADC_HardwareAverage_32,      //32均值
}ADC_HardwareAveMode_Type;

//!< ADC中断及DMA配置选择
typedef enum
{
    kADC_IT_Disable,        //AD中断功能禁止
    kADC_DMA_Disable,       //ADC DMA功能禁止
    kADC_IT_EOF,            //打开ADC 转换完成中断
    kADC_DMA_EOF,           //打开ADC DMA 完成中断
}ADC_ITDMAConfig_Type;

//!< ADC 回调函数定义
typedef void (*ADC_CallBackType)(void);

//!< ADC 初始化结构
typedef struct
{
    uint32_t                    instance;                   //模块号
    ADC_TriggerSelect_Type      triggerMode;                //触发模式 软件触发 或 硬件触发
    ADC_ClockDiv_Type           clockDiv;                   //ADC时钟分频
    ADC_ResolutionMode_Type     resolutionMode;             //分频率选择 8 10 12 16位精度等
    ADC_SingleOrDiffMode_Type   singleOrDiffMode;           //单端 还是 差分输入
    ADC_ContinueMode_Type       continueMode;               //是否启动连续转换
    ADC_HardwareAveMode_Type    hardwareAveMode;            //硬件平均功能选择
    ADC_VoltageRef_Type         vref;                       //模拟电压参考源
}ADC_InitTypeDef;


//!< API functions
void ADC_CallbackInstall(uint32_t instance, ADC_CallBackType AppCBFun);
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
uint8_t ADC_QuickInit(uint32_t MAP, ADC_ResolutionMode_Type resolutionMode);
void ADC_ITDMAConfig(uint32_t instance, uint32_t mux, ADC_ITDMAConfig_Type config);
int32_t ADC_QuickReadValue(uint32_t MAP);
int32_t ADC_ReadValue(uint32_t instance, uint32_t mux);
void ADC_StartConversion(uint32_t instance, uint32_t chl, uint32_t mux);
uint8_t ADC_IsConversionCompleted(uint32_t instance, uint32_t mux);
void ADC_ChlMuxConfig(uint32_t instance, uint32_t mux);


#ifdef __cplusplus
}
#endif



#endif
