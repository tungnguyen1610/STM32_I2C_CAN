/*
* CanCommunication.c
*
* Reference: KovacsV
*/
#include "main.h"
#include "CanCommunication.h"
#include "SevenSegment.h"
#include <string.h>
// TODO 2.1
// Uncomment the following handler declaration:
extern FDCAN_HandleTypeDef hfdcan1;
static uint8_t _deviceId;
static uint32_t _lastUpdateMs;
static int32_t _localCounter=0;
static int32_t _remoteCounters[]={-1,-1,-1,-1};
uint8_t CanCommunication_Init(uint8_t deviceId){
_deviceId=deviceId&3;
// TODO 2.2
// Instantiate a FDCAN_FilterTypeDef type sFilterConfig structure!
// Set the fields of the filter structure:
// Identifier type: standard CAN ID
// Filter index: 0
// Filter type: classic masked
// We want to receive into FIFO0
// Set Filter1 and Filter2 values to accept the following identifiers:
// hex "01X" where X: don't care
// Apply the configuration: HAL_FDCAN_ConfigFilter()
FDCAN_FilterTypeDef sFilterConfig;
sFilterConfig.IdType=FDCAN_STANDARD_ID;
sFilterConfig.FilterIndex=0;
sFilterConfig.FilterType=FDCAN_FILTER_MASK;
sFilterConfig.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;
sFilterConfig.FilterID1=0x010;
// Mask is: ID2
sFilterConfig.FilterID2=0x7F0;
HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig);
	// Don't forget to adjust the number of standard filters in the configuration interface!
	// The HAL_FDCAN_Init() function sets it based on the initialization structure.
	// If we don't know the number of filters in advance, we can try to set it as follows:
	// A more reliable (official) solution is to reinitialize the peripheral:
	// HAL_FDCAN_Stop(&hfdcan1);
	// HAL_FDCAN_Init(&hfdcan1);
	// TODO 2.4.2
	// Set up a receiver filter for messages with the 0x02X identifier
	// Ensure the messages go to FIFO1
	// Don't forget to set the number of filters!
	FDCAN_FilterTypeDef sFilterConfig2;
	sFilterConfig2.IdType=FDCAN_STANDARD_ID;
	sFilterConfig2.FilterIndex=1;
	sFilterConfig2.FilterType=FDCAN_FILTER_MASK;
	sFilterConfig2.FilterConfig=FDCAN_FILTER_TO_RXFIFO1;
	sFilterConfig2.FilterID1=0x020;
	// Mask is: ID2
	sFilterConfig2.FilterID2=0x7F0;
	HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig2);
	hfdcan1.Init.StdFiltersNbr=2;
	MODIFY_REG(hfdcan1.Instance->RXGFC, FDCAN_RXGFC_LSS, (hfdcan1.Init.StdFiltersNbr <<
	FDCAN_RXGFC_LSS_Pos));
	HAL_FDCAN_Start(&hfdcan1);
	// TODO 2.2
	// Set up global filtering: HAL_FDCAN_ConfigGlobalFilter()
	// to reject messages that do not match the filters (FDCAN_REJECT)
	// Also reject remote messages (FDCAN_REJECT_REMOTE)
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,FDCAN_REJECT,FDCAN_REJECT,FDCAN_REJECT_REMOTE,FDCAN_REJ
	ECT_REMOTE);
	return 1;
}
uint8_t CanCommunication_Receive(uint8_t fifoNum,AppCanMessage_t* pMessage){
	uint8_t RxData[12];
	fifoNum&=1;
	HAL_StatusTypeDef status;
	// TODO 2.2
	// Instantiate an FDCAN_RxHeaderTypeDef type RxHeader structure!
	// Check the number of messages in the FIFO using HAL_FDCAN_GetRxFifoFillLevel()
	// If there are no messages, return 0
	// If there are messages, read into the RxHeader and RxData variables
	// If the data length is not 4, return 0
	// Copy the identifier and 4 bytes of data into the variable received in the argument list
	FDCAN_RxHeaderTypeDef RxHeader;
	uint32_t num=HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1,FDCAN_RX_FIFO0+fifoNum);
	if (num==0)
	{
	return 0;
	}
	else
	{

	status=HAL_FDCAN_GetRxMessage(&hfdcan1,FDCAN_RX_FIFO0+fifoNum,&RxHeader,RxData);
	if(RxHeader.DataLength!=4 || status!=HAL_OK)
	{
	return 0;
	}
	}
	pMessage->Id=RxHeader.Identifier;
	memcpy(&pMessage->Message,RxData,4);
	return 1;
	}
	uint8_t CanCommunication_Send(AppCanMessage_t* pMessage){
	uint8_t TxData[4];
	// TODO 2.3
	// Instantiate an FDCAN_TxHeaderTypeDef type TxHeader structure!
	// Fill in the TxHeader structure for sending
	// Choose the identifier based on pMessage->Id
	// Identifier type: standard
	// TxFrameType: FDCAN_DATA_FRAME (not remote)
	// Data length: 4 bytes
	// ErrorStateIndicator: FDCAN_ESI_ACTIVE
	// BitRateSwitch: FDCAN_BRS_OFF, we don't want faster transmission after arbitration
	// FDFormat: FDCAN_CLASSIC_CAN
	// TxEventFifoControl: FDCAN_NO_TX_EVENTS
	// MessageMarker: 0
	// Wait until the transmitter FIFO is not full
	// HAL_FDCAN_GetTxFifoFreeLevel() returns the number of free message slots
	// If there are no free message slots, wait until one becomes available
	// Send this message: HAL_FDCAN_AddMessageToTxFifoQ()
	FDCAN_TxHeaderTypeDef TxHeader;
	TxHeader.Identifier=pMessage->Id;
	TxHeader.IdType=FDCAN_STANDARD_ID;
	TxHeader.TxFrameType=FDCAN_DATA_FRAME;
	TxHeader.DataLength=4;
	TxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch=FDCAN_BRS_OFF;
	TxHeader.FDFormat=FDCAN_CLASSIC_CAN;
	TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker=0;
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1)==0)
	{
	}
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,&TxHeader,TxData);
	return 1;
}
uint8_t CanCommunication_Loop(){
	uint32_t time=HAL_GetTick();
	// TODO 2.4.3
	// Receive from FIFO1
	// Extract the sender identifier from the ID: uint8_t remoteId = msg.Id & 3;
	// If the read is successful, check if _remoteCounters[remoteId] is 1 less than the received data
	// If not, display the received counter on the seven-segment display!
	// The value of _remoteCounters[remoteId] is still the original -1, do not update the display
	// Update _remoteCounters[remoteId] with the received counter value
	AppCanMessage_t received_msg;
	uint8_t remoteId;
	if(CanCommunication_Receive(1,&received_msg))
	{
	remoteId = received_msg.Id & 3;
	if(_remoteCounters[remoteId]==(received_msg.Message-1)){
	//Successful
	}
	else
	{
	SevenSegment_UpdateValueDec(received_msg.Message);
	}
	_remoteCounters[remoteId]=received_msg.Message;
	}
	if (time-_lastUpdateMs<CANCOMMUNICATION_UPDATE_MS){return 0;}
	_lastUpdateMs=time;
	// TODO 2.4.1
	// Create an AppCanMessage_t instance
	// Set the message ID to: 0x020 and use the lower two bits for the device ID
	// Set the message content to _localCounter
	// Increment _localCounter
	// Send the message! CanCommunication_Send()
	AppCanMessage_t send_msg;
	send_msg.Id=0x020|_deviceId;
	send_msg.Message= _localCounter;
	_localCounter++;
	CanCommunication_Send(&send_msg);
	return 1;
}