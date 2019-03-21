/**
 * state_machine.h
 *
 *  Created on: Feb 8, 2019
 *      Author: Szymon Rajca
 */

#include <sys/_stdint.h>
#include <stdbool.h>

typedef void (*fnc_ptr_t)(uint32_t, uint32_t *);

/**
 * A structure to represent state.
 */
typedef struct state_t
{
	/*@{*/
	fnc_ptr_t function; 		/**< The poniter to the executing function.*/
	uint32_t *input; 		/**< The pointer to input for the function.*/
	uint32_t *output; 		/**< The pointer to output fot the function.*/
	struct state_t *next_state; 	/**< The poniter to the next state to execute.*/
	/*@}*/
} state_t;

/**
 * A structure to represent machine.
 */
typedef struct state_machine_t
{
	/*@{*/
	state_t *state_running; 	/**< The pointer to the executing state.*/
	uint32_t states_number; 	/**< The number of states.*/
	state_t *states_list; 		/**< The pointer to list of states.*/
	bool initialized; 		/**< Indicates if the machine was initialized.*/
	/*@}*/
} state_machine_t;

/**
 * @brief 				Initializes the state.
 * @param state_struct 			The pointer to the state struct.
 * @param function_ptr 			The pointer to the function to be execute in the state.
 * @param input 			The pointer to the state's input.
 * @param output 			The pointer to the state's output.
 * @param next_state 			The pointer to the next state to execute.
 * @return 				0 if ok, 1 otherwise.
 */
uint8_t state_initialize(state_t *state_struct, fnc_ptr_t function_ptr,
		uint32_t * const input, uint32_t *output, state_t *next_state);

/**
 * @brief 				Executes the state.
 * @param state_struct 			The pointer to the initialized state's structure.
 * @return 				0 if ok, 1 otherwise.
 */
state_t *state_execute(state_t *state_struct);

/**
 * @brief 				Initializes the state machine.
 * @param machine 			The pointer to the machine struct.
 * @param states_list 			The pointer to the list of states to be executed in the machine.
 * @param states_num 			The number of initialized states.
 * @return 				0 if ok, 1 otherwise.
 */
uint8_t state_machine_initialize(state_machine_t *machine,
		state_t * const states_list, uint32_t states_num);

/**
 * @brief 				Executes the state machine.
 * @param machine 			The pointer to the machine struct.
 * @param state_first 			The poniter to the first state to executed on the machine.
 * @return 				0 if ok, 1 otherwise.
 */
uint8_t state_machine_execute(state_machine_t *machine, state_t *state_first);
s
