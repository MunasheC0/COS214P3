#ifndef RELAYGROUP_H
#define RELAYGROUP_H

#include "EventGroup.h"
#include "EventObserver.h"

/*
 * Design decision: why RelayGroup exists instead of EventGroup itself
 * inheriting EventObserver.
 *
 * If every composite node were an observer, every group in the tree would
 * carry the Observer machinery whether or not it ever takes part in a
 * notification cascade, and it would be unclear which nodes are meant to
 * be attached to a subject. Splitting the role into this subclass keeps
 * plain EventGroup purely structural and makes the cascade topology
 * explicit in the types: only RelayGroup instances are ever attached
 * anywhere (e.g. to EventControl), and a plain EventGroup cannot be —
 * it simply is not an EventObserver, so attach() won't accept it.
 * Attaching one RelayGroup therefore covers its whole subtree with a
 * single attach() call, while groups outside any cascade stay untouched.
 */
/**
 * @brief A group that also listens for notices and relays them down to the
 * observers among its children.
 *
 * Composite (GoF Composite, inherited from EventGroup) and ConcreteObserver
 * (GoF Observer). These are two separate collaborations, not a duplicated
 * pattern: the Composite side owns and manages the subtree, while the
 * Observer side lets the whole subtree be reached through one attach() of
 * this node. On update() it applies its local reaction, then forwards the
 * same notice to every child that is itself an EventObserver.
 */
class RelayGroup : public EventGroup, public EventObserver {
public:
    /**
     * @brief Constructs an empty relay group with a display name and base
     * capacity.
     *
     * @param name Human-readable name of the group.
     * @param capacity Base capacity of the group itself, excluding
     *        children.
     */
    RelayGroup(std::string name, int capacity);

    /**
     * @brief Receives a notice and relays it to all observer children.
     *
     * Logs the relay locally, then forwards the unchanged notice to each
     * child that implements EventObserver (leaves and nested RelayGroups),
     * so the cascade continues down the subtree. Children that are plain
     * EventGroups are skipped, as they have no Observer role.
     *
     * @param notice The notice to relay. Forwarded by const reference;
     *        never stored.
     */
    void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor.
     *
     * Virtual (via both bases) so a RelayGroup deletes correctly through an
     * EventComponent*, EventGroup* or EventObserver* pointer. Child cleanup
     * is inherited from ~EventGroup(); being an observer adds nothing to
     * delete, since subjects never own their observers.
     */
    virtual ~RelayGroup() = default;
};

#endif
