#pragma once
#include <Process/Process.hpp>
#include <AppInteraction/Process/AppInteractionProcessMetadata.hpp>

#include <AppInteraction/SimpleElement/SimpleElement.hpp>
#include <AppInteraction/PolymorphicEntity/PolymorphicEntity.hpp>

#include <State/Address.hpp>

#include <iscore/model/EntityMap.hpp>

namespace AppInteraction
{
class ProcessModel final : public Process::ProcessModel
{
        ISCORE_SERIALIZE_FRIENDS
        MODEL_METADATA_IMPL(AppInteraction::ProcessModel)

        Q_OBJECT
        Q_PROPERTY(::State::AddressAccessor address READ address WRITE setAddress
                       NOTIFY addressChanged)
    public:
        ProcessModel(const TimeVal& duration,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);

        template<typename Impl>
        ProcessModel(Impl& vis, QObject* parent) :
            Process::ProcessModel{vis, parent}
        {
            vis.writeTo(*this);
        }

        ::State::AddressAccessor address() const;
        int interactionType() const;
        int mobileDevice() const;
        void setAddress(const ::State::AddressAccessor& arg);
        void setInteractionType(int);
        void setMobileDevice(int);

        iscore::EntityMap<SimpleElement> simpleElements;
        iscore::EntityMap<PolymorphicEntity> polymorphicEntities;


    signals:
        void addressChanged(const ::State::AddressAccessor&);
        void interactionTypeChanged(int);
        void mobileDeviceChanged(int);

    private:
        ProcessModel(const ProcessModel& source,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);

        QString prettyName() const override;
        void startExecution() override;
        void stopExecution() override;
        void reset() override;
        ProcessStateDataInterface*startStateData() const override;
        ProcessStateDataInterface*endStateData() const override;
        Selection selectableChildren() const override;
        Selection selectedChildren() const override;
        void setSelection(const Selection& s) const override;

        void setDurationAndScale(const TimeVal& newDuration) override;
        void setDurationAndGrow(const TimeVal& newDuration) override;
        void setDurationAndShrink(const TimeVal& newDuration) override;

     ::State::AddressAccessor m_address;
     int m_interactionType;
     int m_mobileDevice;

};
}
