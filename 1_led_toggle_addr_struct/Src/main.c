// WHere is the port and the Pin connected
//  Port: A
// Pin : 5
#include <stdint.h>



#define PERIPH_BASE 					(0x40000000UL)

#define AHB2_PERIPH_OFFSET 				(0x08000000UL)

#define AHB2_PERIPH_BASE 				(PERIPH_BASE + AHB2_PERIPH_OFFSET)

#define GPIOA_PERIPHERAL_OFFSET 		(0x00000000UL)

#define GPIOA_BASE 		                 (AHB2_PERIPH_BASE + GPIOA_PERIPHERAL_OFFSET)

#define GPIOA_OFFSET 					(0x00UL)

#define RCC_OFFSET 						(0x00021000UL)

#define RCC_PERIPH 						*(volatile unsigned int*)(PERIPH_BASE + RCC_OFFSET)

#define AHB_ENABLE_OFFSET 				(0x14UL)

#define RCC_AHBENR						*(volatile unsigned int*)(RCC_PERIPH + AHB_ENABLE_OFFSET)

#define RCC_GPIOAEN						    (1U<<17) // 0x 0000 0000 0010 0000 0000 0000 0000  	// enabling GPIOA

#define GPIOA_MODER 					*(volatile unsigned int*)(GPIOA_BASE + GPIOA_OFFSET)

#define ODR_OFFSET 						(0x14UL)

#define GPIOA_ODR 						*(volatile unsigned int*)(GPIOA_BASE + ODR_OFFSET)


#define GPIOA_MODE_OUTPUT               (1U<<10)




#define PIN_5                           (1U<<5)

#define LED_PIN							PIN_5



#define GPIOA_ADR                           (0x48000000)
#define RCC_ADR 							(0x40021000)

#define RCC_AHBENR_OFFSET					(0x14)

#define __IO volatile

#define GPIOA_ENABLE  (1U << 17)

/*
typedef struct
{

}GPIO_Typedef;
*/

/*
typedef struct
{
	__IO uint32_t MODER; // GPIO port mode register
	__IO uint32_t OTYPER; // GPIO port output type register //
	__IO uint32_t OSPEEDR; //  GPIO port output speed register //
	__IO uint32_t PUPDR; // GPIO port pull-up/ pull-down register //
	__IO uint32_t IDR; // GPIO port input data register //
	__IO uint32_t ODR; // GPIO output data register //
	__IO uint32_t BSRR; // GPIO port bit set reset register //
	__IO uint32_t LCKR; // GPIO port configuration lock register //
	__IO uint32_t AFR[2]; // alternate function low/high register //
	__IO uint32_t BRR; // GPIO port bit reset register //
}GPIO_TypeDef;
*/




typedef struct
{
	volatile uint32_t MODER; // GPIO port mode register
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR; // GPIO output data register //
}GPIO_TypeDef;



typedef struct
{
 volatile uint32_t DUMMY[5];
 volatile uint32_t AHBENR; // AHB peripheral clock enable register
}RCC_TypeDef;



#define RCC  ((RCC_TypeDef*)RCC_ADR)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)




/*
 *  (1U<<10) // Set bit 10 to 1
 *  &= ~(1U<<11))
 *
 *  */




int main()
{
//RCC_AHBENR_enable  |=  (1U<<17);
RCC->AHBENR |= GPIOA_ENABLE;


GPIOA->MODER |= (1U << 10);
GPIOA->MODER &= ~(1U << 11);







//GPIOA_MODER_REGISTER |= (1U<<10);

//GPIOA_ODR_REGISTER |= (1U<5);

	/*
RCC_AHBENR |= RCC_GPIOAEN;

GPIOA_MODER |= GPIOA_MODE_OUTPUT;
GPIOA_MODER &= ~(1U<<11);
	*/




while(1)
{
	//GPIOA_ODR_REGISTER   |= LED_PIN;


	// Experiment 2 : Toggle PIN A5
	//GPIOA_ODR_REGISTER ^= LED_PIN;



	GPIOA->ODR ^= LED_PIN;

	for(int i = 0; i < 100000; i++){}


//	GPIOA->ODR |= LED_PIN;



}


}
