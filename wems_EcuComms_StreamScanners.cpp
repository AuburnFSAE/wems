#include "wems_EcuComms_StreamScanners.h"
WemsEcuBufferBlock wems_EcuComms_Init(si16 n_channel_count, si16 n_comm_pin){

	WemsEcuBufferBlock ecu_block = 
	wems_EcuComms_GetEcuBlock( n_channel_count, n_comm_pin );

	wems_EcuComms_Action = &wems_EcuComms_HeaderScan;
return ecu_block;}

void wems_EcuComms_HeaderScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 31;
    
    if( (comm_blk->bitque & comm_blk->header ) == comm_blk->header ){
		//empty que
		comm_blk->bitque=0;

		comm_blk->scan_complete=0;
		comm_blk->channel_pos=0;
		comm_blk->bit_pos=10-1;

		wems_EcuComms_Action = &wems_EcuComms_CountScan;
    }

return;}

void wems_EcuComms_CountScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 31;
    
    if( comm_blk->bit_pos-- ){
		comm_blk->ecu_channel_count = ((ui32)0x3FC00000 & comm_blk->bitque) >> 20;
		comm_blk->bitque = 0;
		comm_blk->bit_pos=20-1;
		
		wems_EcuComms_Action = &wems_EcuComms_DataScan;
    }
return;}

void wems_EcuComms_DataScan(WemsEcuBufferBlock* comm_blk){
    comm_blk->bitque >>= 1;
    comm_blk->bitque |= ((ui32)digitalRead( comm_blk->comm_pin )) << 31;
    
    if( comm_blk->bit_pos-- ){
		
		comm_blk->bitque >>= 12;
	
		comm_blk->ecu_stream.data[comm_blk->channel_pos] = 
		((comm_blk->bitque &= 0x3FC00) >> 2) | (comm_blk->bitque & 0xFF);

		if( ++comm_blk->channel_pos == comm_blk->num_channels ){
			comm_blk->bitque = 0;
			wems_EcuComms_Action = &wems_EcuComms_VoidScan;
		}
    }
return;}

void wems_EcuComms_VoidScan(WemsEcuBufferBlock* comm_blk){

return;}
