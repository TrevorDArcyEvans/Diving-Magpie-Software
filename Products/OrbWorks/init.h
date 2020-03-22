//---------------------------------------------------------------------------
#ifndef initialiseH
#define initialiseH
//---------------------------------------------------------------------------
#define NUM_OPTIONS             40
#define NUM_BUTTON_OPTS         40
#define NUM_AXIS_OPTS           7

#define SAVE_NUM            	37
#define MODIFIER_NUM            38

#define TYPE_APP                0
#define TYPE_DOC                1
#define TYPE_ASS                2
#define TYPE_DWG                3
//---------------------------------------------------------------------------
#define OW_HANDLE_REG_ERROR     \
            if (regSettings->WasError == true) { WasError = true; goto CLEAN_UP; }
//---------------------------------------------------------------------------
struct OptionType
    {
    char            *Text;
    int             SW_OleType;
    char            *SW_OleProcName;
    int             SW_OleNumParam;
    int             SW_OleParam1;
    };

struct ButtonOptionType
    {
    OptionType      *Option     ;
    };

struct AxisOptionType
    {
    char            *Text;
    OptionType      *OptionMinus;
    OptionType      *OptionPlus ;
    };
//---------------------------------------------------------------------------
extern struct OptionType         Option         [NUM_OPTIONS    ];
extern struct ButtonOptionType   ButtonOption   [NUM_BUTTON_OPTS];
extern struct AxisOptionType     AxisOption     [NUM_AXIS_OPTS  ];
//---------------------------------------------------------------------------
void     InitAxisDropDownList(
            TComboBox        *ddlAxis);

void     InitButtonDropDownList(
            TComboBox        *ddlAxis);

#endif
