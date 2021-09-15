#define ROOD 2
#define GROEN 3
#define ORANJE 4
#define ON 1
#define OFF 0
#define KNIPPEREN 10


int state; // Representeerd de kleurenstatus
int onOff;


/**
 * Functie om de kleur rood te maken
 * */
int turn_red()
{
    digitalWrite(ORANJE, LOW);
    return ROOD;
}


int turn_flickering()
{
    digitalWrite(ORANJE, LOW);
    return KNIPPEREN;
}


/**
 * Functie om de kleur oranje te maken 
 **/
int turn_orange()
{
    digitalWrite(GROEN, LOW);
    return ORANJE;
}


/**
 * Functie om de kleur groen te maken
 **/
int turn_green()
{
    digitalWrite(ROOD, LOW);
    return GROEN;
}


/**
 * Functie voor het checken van de status van orange
 **/
void flip_orange_state()
{
    if (onOff == ON) {
        digitalWrite(ORANJE, HIGH);
    } else {
        digitalWrite(ORANJE, LOW);
    }
}


/**
 * Functie voor het opzetten van de variabelen
 * */
void setup()
{
    pinMode(ROOD, OUTPUT);
    pinMode(GROEN, OUTPUT);
    pinMode(ORANJE, OUTPUT);

    state = ROOD;
    onOff = 1;
}


/**
 * Functie die continue loopt
 **/
void loop()
{
    static unsigned long startTime = millis();

    // Check welke kleuren en welke tijden er op het moment zijn
    switch(state)
    {
        // checkt of de status rood is
        case ROOD:
            digitalWrite(ROOD, HIGH);

            if (millis() - startTime >= 3000) {
                startTime = millis();
                state = turn_green();
            }
        break;
        // Checkt of de status knipperen is
        case KNIPPEREN:
            static unsigned long newTime = startTime;

            flip_orange_state();
            
            if (millis() - newTime >= 100) {
                newTime = millis();
                onOff = !onOff;
            }

            if (millis() - startTime >= 1000) {
                startTime = millis();
                state = turn_red();
            }
        break;
        // Checkt of de status oranje is
        case ORANJE:
            digitalWrite(ORANJE, HIGH);

            if (millis() - startTime >= 1000) {
                startTime = millis();
                state = turn_flickering();
            }
        break;
        // Checkt of de status groen is
        case GROEN:
            digitalWrite(GROEN, HIGH);

            if (millis() - startTime >= 2000) {
                startTime = millis();
                state = turn_orange();
            }
        break;
    }
}