/**
 * state_machine.c
 *
 *  Created on: Feb 8, 2019
 *      Author: Szymon Rajca
 */

#include "state_machine.h"

/**
 * @brief 		The function checks whether the state is defined in the machine list.
 * @param machine 	The pointer to the machine state.
 * @param state 	The pointer to the machine' state.
 * @return 		Boolean.
 */
static bool is_state_in_machine(state_machine_t *machine, state_t *state);

/**
 * @brief 		The function for each state on the machine list checks
 * 			whether the state and its next state is on this list.
 * @param list 		The pointer to the list of states.
 * @param num 		The number of states.
 * @return 		Boolean.
 */
static bool are_states_appropriate(state_t * const list, uint32_t num);

uint8_t state_initialize(state_t *state_struct, fnc_ptr_t function_ptr,
		uint32_t * const input, uint32_t *output, state_t *next_state)
{
	if ((!state_struct) || (!function_ptr))
	{
		return 1;
	}

	state_struct->function = function_ptr;
	state_struct->input = input;
	state_struct->output = output;
	state_struct->next_state = next_state;

	return 0;
}

state_t *state_execute(state_t *state_struct)
{
	if (!state_struct)
	{
		return 0;
	}

	state_struct->function(*state_struct->input, state_struct->output);

	return state_struct->next_state;
}

static bool are_states_appropriate(state_t * const list, uint32_t num)
{
	for (uint32_t i = 0; i < num; i++)
	{
		if ((list + i)->next_state == 0)
		{
			continue;
		}
		uint32_t j = 0;
		for (j = 0; j < num; j++)
		{
			if ((list + i)->next_state == (list + j))
			{
				break;
			}
		}
		if (j == num)
		{
			return false;
		}
	}

	return true;
}

uint8_t state_machine_initialize(state_machine_t *machine,
		state_t * const states_list, uint32_t states_num)
{
	if ((!machine) || (!states_list))
	{
		return 1;
	}

	machine->initialized = false;

	if (!are_states_appropriate(states_list, states_num))
	{
		return 1;
	}

	machine->states_list = states_list;
	machine->states_number = states_num;
	machine->state_running = 0;
	machine->initialized = true;

	return 0;
}

static bool is_state_in_machine(state_machine_t *machine, state_t *state)
{
	uint32_t i = 0;
	for (i = 0; i < machine->states_number; i++)
	{
		if ((machine->states_list + i) == state)
		{
			return true;
		}
	}

	return false;
}

uint8_t state_machine_execute(state_machine_t *machine, state_t *state_first)
{
	if ((!machine) || (!state_first))
	{
		return 1;
	}

	if (!(machine->initialized))
	{
		return 1;
	}

	if (!is_state_in_machine(machine, state_first))
	{
		return 1;
	}

	machine->state_running = state_first;

	while (machine->state_running)
	{
		machine->state_running = state_execute(machine->state_running);
	}

	return 0;
}

