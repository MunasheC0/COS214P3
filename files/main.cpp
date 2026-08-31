#include <iostream>

#include "EventControl.h"
#include "EventGroup.h"
#include "RelayGroup.h"
#include "Stage.h"
#include "Gate.h"
#include "Vendor.h"
#include "MedicalTeam.h"
#include "InfoDesk.h"
#include "ShuttleStop.h"

int main() {
    // Build a tiny festival (Composite)
    EventGroup festival("Mini Fest");

    Stage* mainStage = new Stage("Main Stage", 500);
    Gate* northGate = new Gate("North Gate", 200);
    Vendor* tacoStand = new Vendor("Taco Stand", 30);
    MedicalTeam* medics = new MedicalTeam("Medic Tent", 10);
    InfoDesk* infoDesk = new InfoDesk("Info Desk", 5);
    ShuttleStop* shuttle = new ShuttleStop("Shuttle Stop A", 40);

    // The east field relays notices down to whatever lives inside it
    RelayGroup* eastField = new RelayGroup("East Field", 0);
    eastField->add(tacoStand);
    eastField->add(shuttle);

    festival.add(mainStage);
    festival.add(northGate);
    festival.add(medics);
    festival.add(infoDesk);
    festival.add(eastField);

    // Wire up the Observer side
    EventControl control;
    control.attach(mainStage);
    control.attach(northGate);
    control.attach(medics);
    control.attach(infoDesk);
    control.attach(eastField); // one attach covers the whole subgroup

    std::cout << "=== Opening the festival ===\n";
    festival.open();

    std::cout << "\n=== Status check ===\n";
    festival.reportStatus();
    std::cout << "Total capacity: " << festival.getCapacity() << "\n";

    std::cout << "\n=== Uh oh, weather... ===\n";
    control.issueNotice(NoticeType::WEATHER_ALERT, "Storm rolling in", 3);

    std::cout << "\n=== It got worse ===\n";
    control.issueNotice(NoticeType::EVACUATE, "Everyone out, calmly!", 5);

    std::cout << "\n=== Closing up ===\n";
    festival.close();
    festival.reportStatus();

    // EventGroup's destructor cleans up the children
    return 0;
}
