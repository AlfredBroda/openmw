
#include "armor.hpp"

#include <components/esm/loadarmo.hpp>

#include <components/esm_store/cell_store.hpp>

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontake.hpp"

#include "../mwrender/cellimp.hpp"

#include "containerutil.hpp"

namespace MWClass
{
    void Armor::insertObj (const MWWorld::Ptr& ptr, MWRender::CellRenderImp& cellRender,
        MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Armor, MWWorld::RefData> *ref =
            ptr.get<ESM::Armor>();

        assert (ref->base != NULL);
        const std::string &model = ref->base->model;
        if (!model.empty())
        {
            MWRender::Rendering rendering (cellRender, ref->ref);
            cellRender.insertMesh ("meshes\\" + model);
            cellRender.insertObjectPhysics();
            ref->mData.setHandle (rendering.end (ref->mData.isEnabled()));
        }
    }

    std::string Armor::getName (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Armor, MWWorld::RefData> *ref =
            ptr.get<ESM::Armor>();

        return ref->base->name;
    }

    boost::shared_ptr<MWWorld::Action> Armor::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor, const MWWorld::Environment& environment) const
    {
        return boost::shared_ptr<MWWorld::Action> (
            new MWWorld::ActionTake (ptr));
    }

    bool Armor::hasItemHealth (const MWWorld::Ptr& ptr) const
    {
        return true;
    }

    int Armor::getItemMaxHealth (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Armor, MWWorld::RefData> *ref =
            ptr.get<ESM::Armor>();

        return ref->base->data.health;
    }

    void Armor::insertIntoContainer (const MWWorld::Ptr& ptr,
        MWWorld::ContainerStore<MWWorld::RefData>& containerStore) const
    {
        insertIntoContainerStore (ptr, containerStore.armors);
    }

    std::string Armor::getScript (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Armor, MWWorld::RefData> *ref =
            ptr.get<ESM::Armor>();

        return ref->base->script;
    }

    std::string Armor::getInventoryIcon (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Armor, MWWorld::RefData> *ref =
            ptr.get<ESM::Armor>();

        return ref->base->icon;
    }

    void Armor::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Armor);

        registerClass (typeid (ESM::Armor).name(), instance);
    }
}
