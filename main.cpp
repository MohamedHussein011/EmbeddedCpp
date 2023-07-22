#include "Rcc.h"



int main ()
{
	Rcc Obj;
	Obj.Rcc_EnablePeripheral(Rcc_Apb2, Rcc_Gpioa);
	
	while(1);
}