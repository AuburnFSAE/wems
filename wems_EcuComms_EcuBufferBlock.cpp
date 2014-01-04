#include "wems_EcuComms_EcuBufferBlock.h"

ui32 wems_EcuComms_GetHeader(void){
	ui32 stop = 0x01;
    
    ui32 header = (0x82);
    header |= stop << 8;

    header |= (ui32)0x81 << 10 ;
    header |= stop << 18;

    header |= (ui32)0x80 << 20;
    header |= stop<<28;

return header;}

WemsEcuBufferBlock wems_EcuComms_GetEcuBlock(si16 n_num_channels, si16 n_comm_pin){
	WemsEcuBufferBlock ecu_block;

	ecu_block.header = wems_EcuComms_GetHeader();

	ecu_block.ecu_stream = wems_DataStream_GetSI16( n_num_channels );

	ecu_block.scan_complete=0;
	ecu_block.bitque=0;
	ecu_block.num_channels=n_num_channels;
	ecu_block.channel_pos=0;
	ecu_block.bit_pos=0;
	ecu_block.ecu_channel_count=0;
	ecu_block.comm_pin = n_comm_pin;
return ecu_block;}
