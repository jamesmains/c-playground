#ifndef STATS_H
#define STATS_H
#define HEALTH_STAT_ID 4


// Todo: need to find a use for these stats...
typedef enum {
    STAT_STR, // 0
    STAT_DEX, // 1  | Currently only used for steps per explore turn
    STAT_INT, // 2
    STAT_END, // 3  | 
    STAT_VIT, // 4  | Unlike many RPGs this is used as health, not a modifier to it
    STAT_COUNT
} StatType;

typedef enum {
    ATR_PHYSICAL,
    ATR_FIRE,
    ATR_ICE,
    ATR_LIGHTNING,
    ATR_POISON,
    ATR_COUNT
} AttributeType;

typedef struct Stat{
    StatType id;        // Unique identifier for the stat
    int base_value;     // The base value of the stat without any modifiers
    int current_value;  // The current value of the stat, including modifiers
    int modifier;       // The modifier to be added to the base value
} Stat;

typedef struct Attribute{
    AttributeType id;   // Unique identifier for the attribute
    int resistance;     // Resistance value against this attribute
    int weakness;       // Weakness value against this attribute
} Attribute;

#endif