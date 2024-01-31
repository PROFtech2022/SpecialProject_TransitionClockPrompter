//Variables used in this system are written here
uint32_t last_millis = 0;
uint32_t LEDseg_IntCounter = 0;

bool CalibrationMode = false;

bool LEDseg_CalibToggle = false;

//prompt times
#define p_ArrivalTime 0x00
#define p_MeetingTime 0x01
#define p_StoryTime 0x02
#define p_ActivityTime 0x03
#define p_IndoorOutdoorTime 0x04
#define p_NapTime 0x05
#define p_CircleTime 0x06
#define p_GoodbyeTime 0x07



uint8_t pTime_Minute[8];
uint8_t pTime_Second[8];

bool CurrentPT_Started=false;
uint32_t CurrentPT_IntCounter=0;

uint8_t currentPT_Minute=15;
uint8_t currentPT_Second=0;

bool stepper_stepped=false;
uint8_t step_counter=0;

bool arrow90Detected=false;

bool BuzzToggle=false;

uint32_t arrowHeadCounter=0;