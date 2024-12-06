/*****************************************************************************************************************************
**********************************    Author  : Ehab Magdy Abdullah                      *************************************
**********************************    Linkedin: https://www.linkedin.com/in/ehabmagdyy/  *************************************
**********************************    Youtube : https://www.youtube.com/@EhabMagdyy      *************************************
******************************************************************************************************************************/

/* USER CODE BEGIN PV */
volatile uint8_t bitCount = 0;
volatile uint8_t isStartCaptured = 0;
volatile uint32_t receivedData = 0;
static volatile uint8_t isRisingCaptured = 0;
static volatile uint32_t IC_Value = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(0 == bitCount && 0 == isStartCaptured && 0 == receivedData)
	{
		isStartCaptured = 1;
	}
	else if(0 == bitCount && 1 == isStartCaptured && 0 == receivedData)
	{
		__HAL_TIM_SET_COUNTER(htim, 0);
		isStartCaptured = 2;
	}
	else if(32 > bitCount)
	{
		IC_Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COUNTER(htim, 0);
		// Received Logic '0'
		if(1000 < IC_Value && 1300 > IC_Value)
		{
			receivedData &= ~(1 << bitCount);
		}
		// Received Logic '1'
		if(2100 < IC_Value && 2400 > IC_Value)
		{
			receivedData |= (1 << bitCount);
		}
		bitCount++;
		if(bitCount == 32)
		    HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
	}

}
/* USER CODE END PFP */

int main(void)
{
  /* USER CODE BEGIN 2 */
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Main loop, process received data
	  if (32 <= bitCount)
	  {
		  // take your actions on received data
		  HAL_Delay(500);
		  bitCount = 0;
		  receivedData = 0;
		  isStartCaptured = 0;
		  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

