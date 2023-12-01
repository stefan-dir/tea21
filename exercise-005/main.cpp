#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * The inernal states
 */
typedef enum {
    STATE_OBEN         = 0,
    STATE_UNTEN        = 1,
    STATE_FAHRE_HOCH   = 2,
    STATE_FAHRE_RUNTER = 3,
    STATE_STOP_HOCH    = 4,
    STATE_STOP_RUNTER  = 5,
    STATE_ERROR        = 6,
    STATE_MAX
} StatemachineState_t;

typedef enum {
    EV_TASTE               = 0,
    EV_ENDSCHALTER_OBEN    = 1,
    EV_ENDSCHALTER_UNTEN   = 2,
    EV_MAX
} Event_t;


int error(Event_t e)
{
    fmt::println("Error detected! Event: {}",(int)e);
    return EXIT_FAILURE;
}

int state_oben(Event_t e)
{
    fmt::println("Aktueller Zustand: OBEN Event: {}",(int)e);
    return EXIT_SUCCESS;
}

int state_unten(Event_t e)
{
    fmt::println("Aktueller Zustand: UNTEN Event: {}",(int)e);
    return EXIT_SUCCESS;
}

int state_fahre_hoch(Event_t e)
{
    fmt::println("Aktueller Zustand: FAHRE_HOCH Event: {}",(int)e);
    return EXIT_SUCCESS;
}

int state_fahre_runter(Event_t e)
{
    fmt::println("Aktueller Zustand: FAHRE_RUNTER Event: {}",(int)e);
    return EXIT_SUCCESS;
}

int state_stop_runter(Event_t e)
{
    fmt::println("Aktueller Zustand: STOP_RUNTER Event: {}",(int)e);
    return EXIT_SUCCESS;
}

int state_stop_hoch(Event_t e)
{
    fmt::println("Aktueller Zustand: STOP_HOCH Event: {}",(int)e);
    return EXIT_SUCCESS;
}

typedef int (*stateHandler_t)(Event_t e);

typedef struct {
    StatemachineState_t nextState;
    stateHandler_t hdl;
}StateTuple_t;

typedef struct MyState{
    StatemachineState_t state; /*< The state   */
} MyState_t;



static StateTuple_t TransitionTable[EV_MAX][STATE_MAX] = {
    /*                             STATE_OBEN                                STATE_UNTEN                           STATE_FAHRE_HOCH                          STATE_FAHRE_RUNTER                     STATE_STOP_HOCH                          STATE_STOP_RUNTER */ 
    /* EV_TASTE              */ { {STATE_FAHRE_RUNTER,state_fahre_runter},  {STATE_FAHRE_HOCH,state_fahre_hoch},  {STATE_STOP_HOCH,state_stop_hoch},        {STATE_STOP_RUNTER,state_stop_runter}, {STATE_FAHRE_RUNTER,state_fahre_runter}, {STATE_FAHRE_HOCH,state_fahre_hoch} },
    /* EV_ENDSCHALTER_OBEN   */ { {STATE_OBEN,state_oben},                  {STATE_ERROR,error},                  {STATE_OBEN,state_oben},                  {STATE_ERROR,error},                   {STATE_ERROR,error},                     {STATE_ERROR,error},                },
    /* EV_ENDSCHALTER_UNTEN  */ { {STATE_ERROR,error},                      {STATE_UNTEN,state_unten},            {STATE_ERROR,error},                      {STATE_UNTEN,state_unten},             {STATE_ERROR,error},                     {STATE_ERROR,error},                }
};


MyState_t* myStatemachine_create(void)
{
    MyState_t* ret = (MyState_t*)malloc(sizeof(MyState_t));
    if(NULL != ret)
    {
        memset(ret,0,sizeof(MyState_t));
        ret->state = STATE_FAHRE_HOCH;
    }
    return ret;
}

void myStatemachine_free(MyState_t* statemachine)
{
    if(NULL != statemachine)
    {
        free(statemachine);
    }
}

int myStatemachine_handle(MyState_t* statemachine, Event_t event)
{
    int ret = 1;
    if(   ((STATE_OBEN <= statemachine->state) && (STATE_MAX > statemachine->state)))
    {
        StateTuple_t state = TransitionTable[event][statemachine->state];
        statemachine->state = state.nextState;
        ret = state.hdl(event);
    }
    return ret;
}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

        Event_t test[] = { EV_ENDSCHALTER_OBEN,
        EV_TASTE,
        EV_TASTE,
        EV_TASTE,
        EV_ENDSCHALTER_OBEN,
    };
    int i = 0;

    MyState_t* machine = myStatemachine_create();

    for(i = 0; i < sizeof(test)/sizeof(Event_t); i++)
    {
        myStatemachine_handle(machine,test[i]);
    }

    myStatemachine_free(machine);
    return 0;

    return 0; /* exit gracefully*/
}
