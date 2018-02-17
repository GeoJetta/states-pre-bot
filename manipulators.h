#define MOGO_DOWN_POS 1000
#define MOGO_UP_POS 0

#define CHAINBAR_SCORE_POS 1000
#define CHAINBAR_IDLE_UP_POS 666
#define CHAINBAR_IDLE_DOWN_POS 333
#define CHAINBAR_PICKUP_POS 0

void setMogo( int pwr )
{

	motor[ mogo ] = pwr;

}

void setChainbar( int pwr )
{

	motor[ lChain ] = motor[ rChain ] = pwr;

}
