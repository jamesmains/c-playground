#include "entities.h"
#include "stats.h"
#include "game.h"
#include <stdio.h>

void player_combat_logic(Entity *user, Entity *target, const Item *item)
{
    int max_items = 0;

    // 1. Count and Display
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (user->inventory[i].id != 0)
        {
            printf("[%d] %s |", i, user->inventory[i].name);
            if (user->inventory[i].use_type == DURABLE)
            {
                printf(" Durability %d/%d\n", user->inventory[i].uses_remaining, user->inventory[i].max_uses);
            }
            else if (user->inventory[i].use_type == CASTS)
            {
                printf(" Casts Remaining: %d\n", user->inventory[i].uses_remaining);
            }
            else
            {
                printf("\n");
            }
            max_items++;
        }
        else
            break;
    }

    if (max_items == 0)
        return;

    int choice = -1;
    while (choice == -1)
    {
        printf("Choose action: ");

        // 2. The scanf fix
        if (scanf("%d", &choice) != 1)
        {
            // If user typed a letter, clear the garbage out of the buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        // Also clear the newline after a successful number entry
        while (getchar() != '\n')
            ;

        if (choice >= 0 && choice < max_items)
        {
            Item *selected = &user->inventory[choice];

            if (selected->effect != NULL)
            {
                selected->effect(user, target, selected);
                selected->uses_remaining--;

                if (selected->uses_remaining <= 0)
                {
                    // Using your current function logic (1-based)
                    remove_item_at_index(user, choice + 1);
                }
            }
        }
        else
        {
            printf("Invalid choice!\n");
            choice = -1; // Keep looping
        }
    }
}

void win_match(Entity *player, Entity *opponent)
{
    player->gold += opponent->gold;

    player->kills += 1;
    int base_exp_reward = opponent->level * NEW_LEVEL_EXP_INCREMENT / 2;
    int level_diff = player->level - opponent->level;
    if (level_diff < 0)
        level_diff = 0; // No negative diff
    int curved_exp_reward = base_exp_reward - (level_diff) * opponent->level * 10;
    player->current_exp += curved_exp_reward;
    printf("You earned %d gold and %d EXP!\n", opponent->gold, curved_exp_reward);
    if (player->current_exp >= player->exp_to_next_level)
    {
        player->current_exp -= player->exp_to_next_level;
        player->level += 1;
        
        player->exp_to_next_level = player->level * player->level * NEW_LEVEL_EXP_INCREMENT;
        printf("You leveled up! You are now level %d!\n", player->level);
    }
}

void default_ai_combat_logic(Entity *user, Entity *target, const Item *item)
{
    // Simple AI: just use the first item in inventory if available
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (user->inventory[i].id != 0)
        {
            Item *item = &user->inventory[i];
            item->effect(user, target, item);
            item->uses_remaining--;
            if (item->uses_remaining <= 0)
            {
                // Remove item from inventory
                remove_item_at_index(user, i + 1);
            }
            return;
        }
    }
    // If no items, do nothing for now
    printf("%s has no items to use!\n", user->name);
}

void take_damage(Entity *target, int damage, int attribute_id)
{
    // Apply attribute resistance/weakness
    int resistance = target->attributes[attribute_id].resistance;
    int weakness = target->attributes[attribute_id].weakness;

    damage -= resistance;
    damage += weakness;

    if (damage < 1)
    {
        damage = 1; // Ensure at least 1 damage is dealt
    }

    target->stats[HEALTH_STAT_ID].current_value -= damage;
    if (target->stats[HEALTH_STAT_ID].current_value < 0)
        target->stats[HEALTH_STAT_ID].current_value = 0;
    printf("Result: %s took %d damage! Resisted %d! (%d HP remaining)\n",
           target->name, damage, resistance, target->stats[HEALTH_STAT_ID].current_value);
}

void remove_item_at_index(Entity *p, int index)
{
    printf("Removing item at index %d from %s's inventory.\n", index - 1, p->name);
    if (index < 0 || index >= INVENTORY_SIZE)
    {
        printf("Invalid inventory index!\n");
        return;
    }
    p->inventory[index - 1].id = 0; // Reset the item slot to an empty item
    for (int i = index - 1; i < INVENTORY_SIZE - 1; i++)
    {
        p->inventory[i] = p->inventory[i + 1];
    }
    p->inventory[INVENTORY_SIZE - 1].id = 0; // Clear the last slot
}

void add_item(Entity *p, Item item)
{
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (p->inventory[i].id == 0)
        {
            p->inventory[i] = item;
            printf("Added %s to %s's inventory.\n", item.name, p->name);
            return;
        }
    }
    printf("%s's inventory is full! Cannot add %s.\n", p->name, item.name);
}