
#include "lockpick.hpp"

#include <components/esm/loadlocks.hpp>

#include <components/esm_store/cell_store.hpp>

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontake.hpp"

#include "../mwrender/cellimp.hpp"

#include "containerutil.hpp"

namespace MWClass
{
    void Lockpick::insertObj (const MWWorld::Ptr& ptr, MWRender::CellRenderImp& cellRender,
        MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Tool, MWWorld::RefData> *ref =
            ptr.get<ESM::Tool>();

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

    std::string Lockpick::getName (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Tool, MWWorld::RefData> *ref =
            ptr.get<ESM::Tool>();

        return ref->base->name;
    }

    boost::shared_ptr<MWWorld::Action> Lockpick::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor, const MWWorld::Environment& environment) const
    {
        return boost::shared_ptr<MWWorld::Action> (
            new MWWorld::ActionTake (ptr));
    }

    void Lockpick::insertIntoContainer (const MWWorld::Ptr& ptr,
        MWWorld::ContainerStore<MWWorld::RefData>& containerStore) const
    {
        insertIntoContainerStore (ptr, containerStore.lockpicks);
    }

    std::string Lockpick::getScript (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Tool, MWWorld::RefData> *ref =
            ptr.get<ESM::Tool>();

        return ref->base->script;
    }

    std::string Lockpick::getInventoryIcon (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Tool, MWWorld::RefData> *ref =
            ptr.get<ESM::Tool>();

        return ref->base->icon;
    }

    void Lockpick::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Lockpick);

        registerClass (typeid (ESM::Tool).name(), instance);
    }
}
