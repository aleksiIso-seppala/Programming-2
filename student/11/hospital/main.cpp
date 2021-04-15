/* Hospital
 *
 * Description:
 * the program implemetns an user interface for a hospital.
 * Various thing things can be done in the interface by
 * writing commands. The program checks all the users inputs
 * and ends when the user inputs the quit command.
 *
 * New patients and staff can be added to the hospital. The
 * patients can be assigned medicine and staff can be assigned
 * to the patients care periods. The medicine sticks with the
 * patient even when they leave the hospital. The same patient
 * can come and go from the hospital always with a new care_period
 * and the previous visit are still stored.
 *
 * There are also various printing functions in the program.
 * All patients and all current patients can be printed. It's
 * also possible to print all medicines prescribed in the hospital
 * and the information of a single patient. All the staff_members can
 * be printed and all their care periods can be printed.
 *
 * The program also has a date set in it, so the care periods are in order.
 * The date can be advanced and a new date can be set entirely.
 *
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username  : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 *
 * */

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
