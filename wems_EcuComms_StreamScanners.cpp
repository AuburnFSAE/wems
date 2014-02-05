#include "wems_EcuComms_StreamScanners.h"

void (*wems_EcuComms_Action)(WemsEcuBufferBlock*) = &wems_EcuComms_HeaderScan;

WemsEcuBufferBlock* wems_EcuComms_Init(si16 n_channel_count, si16 n_comm_pin){

	WemsEcuBufferBlock* ecu_block = 
	wems_EcuComms_GetEcuBlock( n_channel_count, n_comm_pin );
	ecu_block->scan_complete = 0;

return ecu_block;}
bool t=0;
void wems_EcuComms_HeaderScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 31;


    
    if( (comm_blk->bitque & HEADERMASK ) == comm_blk->header ){
		//empty que
		//comm_blk->bitque=0;

		comm_blk->scan_complete=0;
		comm_blk->channel_pos=0;
		comm_blk->bit_pos=30;

		wems_EcuComms_Action = &wems_EcuComms_CountScan;
		//Serial.print(comm_blk->header,HEX);
		//wems_EcuComms_Action = &wems_EcuComms_HeaderScan;
		//wems_EcuComms_Action = &wems_EcuComms_VoidScan;

    }

return;}

void wems_EcuComms_CountScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 31;
    comm_blk->bit_pos--;

    if( comm_blk->bit_pos == 0 ){
		comm_blk->ecu_channel_count = (0x00FFu & comm_blk->bitque);
		comm_blk->bitque >>= 10;
		comm_blk->bit_pos=21;
		
		//wems_EcuComms_Action = &wems_EcuComms_HeaderScan;
		wems_EcuComms_Action = &wems_EcuComms_DataScan;
    }
return;}

void wems_EcuComms_DataScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 21;
    comm_blk->bit_pos--;

    if( comm_blk->bit_pos == 0 ){
		
		
		comm_blk->bit_pos=21;
	
		comm_blk->ecu_stream.data[comm_blk->channel_pos] = 
		((comm_blk->bitque &= 0x3FC00u) >> 2) | (comm_blk->bitque & 0xFF);

		if( ++comm_blk->channel_pos == comm_blk->num_channels ){
			comm_blk->bitque = 0;
			comm_blk->scan_complete=1;
			wems_EcuComms_Action = &wems_EcuComms_ResetHeaderWait;
			digitalWrite(10, t=!t);
		}
    }
return;}

void wems_EcuComms_VoidScan(WemsEcuBufferBlock* comm_blk){return;}

void wems_EcuComms_ResetHeaderWait(WemsEcuBufferBlock* comm_blk){

	if( comm_blk->scan_complete == 0)
		wems_EcuComms_Action = &wems_EcuComms_HeaderScan;

return;} 
