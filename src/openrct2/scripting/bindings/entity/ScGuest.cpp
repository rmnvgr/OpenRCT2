/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#ifdef ENABLE_SCRIPTING

#    include "ScGuest.hpp"

#    include "../../../entity/Guest.h"
#    include "../../../localisation/Localisation.h"

namespace OpenRCT2::Scripting
{
    static const DukEnumMap<PeepThoughtType> ThoughtTypeMap({
        { "cant_afford_ride", PeepThoughtType::CantAffordRide },
        { "spent_money", PeepThoughtType::SpentMoney },
        { "sick", PeepThoughtType::Sick },
        { "very_sick", PeepThoughtType::VerySick },
        { "more_thrilling", PeepThoughtType::MoreThrilling },
        { "intense", PeepThoughtType::Intense },
        { "havent_finished", PeepThoughtType::HaventFinished },
        { "sickening", PeepThoughtType::Sickening },
        { "bad_value", PeepThoughtType::BadValue },
        { "go_home", PeepThoughtType::GoHome },
        { "good_value", PeepThoughtType::GoodValue },
        { "already_got", PeepThoughtType::AlreadyGot },
        { "cant_afford_item", PeepThoughtType::CantAffordItem },
        { "not_hungry", PeepThoughtType::NotHungry },
        { "not_thirsty", PeepThoughtType::NotThirsty },
        { "drowning", PeepThoughtType::Drowning },
        { "lost", PeepThoughtType::Lost },
        { "was_great", PeepThoughtType::WasGreat },
        { "queuing_ages", PeepThoughtType::QueuingAges },
        { "tired", PeepThoughtType::Tired },
        { "hungry", PeepThoughtType::Hungry },
        { "thirsty", PeepThoughtType::Thirsty },
        { "toilet", PeepThoughtType::Toilet },
        { "cant_find", PeepThoughtType::CantFind },
        { "not_paying", PeepThoughtType::NotPaying },
        { "not_while_raining", PeepThoughtType::NotWhileRaining },
        { "bad_litter", PeepThoughtType::BadLitter },
        { "cant_find_exit", PeepThoughtType::CantFindExit },
        { "get_off", PeepThoughtType::GetOff },
        { "get_out", PeepThoughtType::GetOut },
        { "not_safe", PeepThoughtType::NotSafe },
        { "path_disgusting", PeepThoughtType::PathDisgusting },
        { "crowded", PeepThoughtType::Crowded },
        { "vandalism", PeepThoughtType::Vandalism },
        { "scenery", PeepThoughtType::Scenery },
        { "very_clean", PeepThoughtType::VeryClean },
        { "fountains", PeepThoughtType::Fountains },
        { "music", PeepThoughtType::Music },
        { "balloon", PeepThoughtType::Balloon },
        { "toy", PeepThoughtType::Toy },
        { "map", PeepThoughtType::Map },
        { "photo", PeepThoughtType::Photo },
        { "umbrella", PeepThoughtType::Umbrella },
        { "drink", PeepThoughtType::Drink },
        { "burger", PeepThoughtType::Burger },
        { "chips", PeepThoughtType::Chips },
        { "ice_cream", PeepThoughtType::IceCream },
        { "candyfloss", PeepThoughtType::Candyfloss },
        { "pizza", PeepThoughtType::Pizza },
        { "popcorn", PeepThoughtType::Popcorn },
        { "hot_dog", PeepThoughtType::HotDog },
        { "tentacle", PeepThoughtType::Tentacle },
        { "hat", PeepThoughtType::Hat },
        { "toffee_apple", PeepThoughtType::ToffeeApple },
        { "tshirt", PeepThoughtType::Tshirt },
        { "doughnut", PeepThoughtType::Doughnut },
        { "coffee", PeepThoughtType::Coffee },
        { "chicken", PeepThoughtType::Chicken },
        { "lemonade", PeepThoughtType::Lemonade },
        { "wow", PeepThoughtType::Wow },
        { "wow2", PeepThoughtType::Wow2 },
        { "watched", PeepThoughtType::Watched },
        { "balloon_much", PeepThoughtType::BalloonMuch },
        { "toy_much", PeepThoughtType::ToyMuch },
        { "map_much", PeepThoughtType::MapMuch },
        { "photo_much", PeepThoughtType::PhotoMuch },
        { "umbrella_much", PeepThoughtType::UmbrellaMuch },
        { "drink_much", PeepThoughtType::DrinkMuch },
        { "burger_much", PeepThoughtType::BurgerMuch },
        { "chips_much", PeepThoughtType::ChipsMuch },
        { "ice_cream_much", PeepThoughtType::IceCreamMuch },
        { "candyfloss_much", PeepThoughtType::CandyflossMuch },
        { "pizza_much", PeepThoughtType::PizzaMuch },
        { "popcorn_much", PeepThoughtType::PopcornMuch },
        { "hot_dog_much", PeepThoughtType::HotDogMuch },
        { "tentacle_much", PeepThoughtType::TentacleMuch },
        { "hat_much", PeepThoughtType::HatMuch },
        { "toffee_apple_much", PeepThoughtType::ToffeeAppleMuch },
        { "tshirt_much", PeepThoughtType::TshirtMuch },
        { "doughnut_much", PeepThoughtType::DoughnutMuch },
        { "coffee_much", PeepThoughtType::CoffeeMuch },
        { "chicken_much", PeepThoughtType::ChickenMuch },
        { "lemonade_much", PeepThoughtType::LemonadeMuch },
        { "photo2", PeepThoughtType::Photo2 },
        { "photo3", PeepThoughtType::Photo3 },
        { "photo4", PeepThoughtType::Photo4 },
        { "pretzel", PeepThoughtType::Pretzel },
        { "hot_chocolate", PeepThoughtType::HotChocolate },
        { "iced_tea", PeepThoughtType::IcedTea },
        { "funnel_cake", PeepThoughtType::FunnelCake },
        { "sunglasses", PeepThoughtType::Sunglasses },
        { "beef_noodles", PeepThoughtType::BeefNoodles },
        { "fried_rice_noodles", PeepThoughtType::FriedRiceNoodles },
        { "wonton_soup", PeepThoughtType::WontonSoup },
        { "meatball_soup", PeepThoughtType::MeatballSoup },
        { "fruit_juice", PeepThoughtType::FruitJuice },
        { "soybean_milk", PeepThoughtType::SoybeanMilk },
        { "sujongkwa", PeepThoughtType::Sujongkwa },
        { "sub_sandwich", PeepThoughtType::SubSandwich },
        { "cookie", PeepThoughtType::Cookie },
        { "roast_sausage", PeepThoughtType::RoastSausage },
        { "photo2_much", PeepThoughtType::Photo2Much },
        { "photo3_much", PeepThoughtType::Photo3Much },
        { "photo4_much", PeepThoughtType::Photo4Much },
        { "pretzel_much", PeepThoughtType::PretzelMuch },
        { "hot_chocolate_much", PeepThoughtType::HotChocolateMuch },
        { "iced_tea_much", PeepThoughtType::IcedTeaMuch },
        { "funnel_cake_much", PeepThoughtType::FunnelCakeMuch },
        { "sunglasses_much", PeepThoughtType::SunglassesMuch },
        { "beef_noodles_much", PeepThoughtType::BeefNoodlesMuch },
        { "fried_rice_noodles_much", PeepThoughtType::FriedRiceNoodlesMuch },
        { "wonton_soup_much", PeepThoughtType::WontonSoupMuch },
        { "meatball_soup_much", PeepThoughtType::MeatballSoupMuch },
        { "fruit_juice_much", PeepThoughtType::FruitJuiceMuch },
        { "soybean_milk_much", PeepThoughtType::SoybeanMilkMuch },
        { "sujongkwa_much", PeepThoughtType::SujongkwaMuch },
        { "sub_sandwich_much", PeepThoughtType::SubSandwichMuch },
        { "cookie_much", PeepThoughtType::CookieMuch },
        { "roast_sausage_much", PeepThoughtType::RoastSausageMuch },
        { "help", PeepThoughtType::Help },
        { "running_out", PeepThoughtType::RunningOut },
        { "new_ride", PeepThoughtType::NewRide },
        { "nice_ride_deprecated", PeepThoughtType::NiceRideDeprecated },
        { "excited_deprecated", PeepThoughtType::ExcitedDeprecated },
        { "here_we_are", PeepThoughtType::HereWeAre },
    });

    ScGuest::ScGuest(EntityId id)
        : ScPeep(id)
    {
    }

    void ScGuest::Register(duk_context* ctx)
    {
        dukglue_set_base_class<ScPeep, ScGuest>(ctx);
        dukglue_register_property(ctx, &ScGuest::tshirtColour_get, &ScGuest::tshirtColour_set, "tshirtColour");
        dukglue_register_property(ctx, &ScGuest::trousersColour_get, &ScGuest::trousersColour_set, "trousersColour");
        dukglue_register_property(ctx, &ScGuest::balloonColour_get, &ScGuest::balloonColour_set, "balloonColour");
        dukglue_register_property(ctx, &ScGuest::hatColour_get, &ScGuest::hatColour_set, "hatColour");
        dukglue_register_property(ctx, &ScGuest::umbrellaColour_get, &ScGuest::umbrellaColour_set, "umbrellaColour");
        dukglue_register_property(ctx, &ScGuest::happiness_get, &ScGuest::happiness_set, "happiness");
        dukglue_register_property(ctx, &ScGuest::happinessTarget_get, &ScGuest::happinessTarget_set, "happinessTarget");
        dukglue_register_property(ctx, &ScGuest::nausea_get, &ScGuest::nausea_set, "nausea");
        dukglue_register_property(ctx, &ScGuest::nauseaTarget_get, &ScGuest::nauseaTarget_set, "nauseaTarget");
        dukglue_register_property(ctx, &ScGuest::hunger_get, &ScGuest::hunger_set, "hunger");
        dukglue_register_property(ctx, &ScGuest::thirst_get, &ScGuest::thirst_set, "thirst");
        dukglue_register_property(ctx, &ScGuest::toilet_get, &ScGuest::toilet_set, "toilet");
        dukglue_register_property(ctx, &ScGuest::mass_get, &ScGuest::mass_set, "mass");
        dukglue_register_property(ctx, &ScGuest::minIntensity_get, &ScGuest::minIntensity_set, "minIntensity");
        dukglue_register_property(ctx, &ScGuest::maxIntensity_get, &ScGuest::maxIntensity_set, "maxIntensity");
        dukglue_register_property(ctx, &ScGuest::nauseaTolerance_get, &ScGuest::nauseaTolerance_set, "nauseaTolerance");
        dukglue_register_property(ctx, &ScGuest::cash_get, &ScGuest::cash_set, "cash");
        dukglue_register_property(ctx, &ScGuest::isInPark_get, nullptr, "isInPark");
        dukglue_register_property(ctx, &ScGuest::isLost_get, nullptr, "isLost");
        dukglue_register_property(ctx, &ScGuest::lostCountdown_get, &ScGuest::lostCountdown_set, "lostCountdown");
        dukglue_register_property(ctx, &ScGuest::thoughts_get, nullptr, "thoughts");
        dukglue_register_property(ctx, &ScGuest::items_get, nullptr, "items");
        dukglue_register_method(ctx, &ScGuest::has_item, "hasItem");
        dukglue_register_method(ctx, &ScGuest::give_item, "giveItem");
        dukglue_register_method(ctx, &ScGuest::remove_item, "removeItem");
        dukglue_register_method(ctx, &ScGuest::remove_all_items, "removeAllItems");
    }

    Guest* ScGuest::GetGuest() const
    {
        return ::GetEntity<Guest>(_id);
    }

    uint8_t ScGuest::tshirtColour_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->TshirtColour : 0;
    }
    void ScGuest::tshirtColour_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->TshirtColour = value;
            peep->Invalidate();
        }
    }

    uint8_t ScGuest::trousersColour_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->TrousersColour : 0;
    }
    void ScGuest::trousersColour_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->TrousersColour = value;
            peep->Invalidate();
        }
    }

    uint8_t ScGuest::balloonColour_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->BalloonColour : 0;
    }
    void ScGuest::balloonColour_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->BalloonColour = value;
            peep->Invalidate();
        }
    }

    uint8_t ScGuest::hatColour_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->HatColour : 0;
    }
    void ScGuest::hatColour_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->HatColour = value;
            peep->Invalidate();
        }
    }

    uint8_t ScGuest::umbrellaColour_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->UmbrellaColour : 0;
    }
    void ScGuest::umbrellaColour_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->UmbrellaColour = value;
            peep->Invalidate();
        }
    }

    uint8_t ScGuest::happiness_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Happiness : 0;
    }
    void ScGuest::happiness_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Happiness = value;
        }
    }

    uint8_t ScGuest::happinessTarget_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->HappinessTarget : 0;
    }
    void ScGuest::happinessTarget_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->HappinessTarget = value;
        }
    }

    uint8_t ScGuest::nausea_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Nausea : 0;
    }
    void ScGuest::nausea_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Nausea = value;
        }
    }

    uint8_t ScGuest::nauseaTarget_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->NauseaTarget : 0;
    }
    void ScGuest::nauseaTarget_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->NauseaTarget = value;
        }
    }

    uint8_t ScGuest::hunger_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Hunger : 0;
    }
    void ScGuest::hunger_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Hunger = value;
        }
    }

    uint8_t ScGuest::thirst_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Thirst : 0;
    }
    void ScGuest::thirst_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Thirst = value;
        }
    }

    uint8_t ScGuest::toilet_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Toilet : 0;
    }
    void ScGuest::toilet_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Toilet = value;
        }
    }

    uint8_t ScGuest::mass_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Mass : 0;
    }
    void ScGuest::mass_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Mass = value;
        }
    }

    uint8_t ScGuest::minIntensity_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Intensity.GetMinimum() : 0;
    }
    void ScGuest::minIntensity_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Intensity = peep->Intensity.WithMinimum(value);
        }
    }

    uint8_t ScGuest::maxIntensity_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->Intensity.GetMaximum() : 0;
    }
    void ScGuest::maxIntensity_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->Intensity = peep->Intensity.WithMaximum(value);
        }
    }

    uint8_t ScGuest::nauseaTolerance_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? EnumValue(peep->NauseaTolerance) : 0;
    }
    void ScGuest::nauseaTolerance_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->NauseaTolerance = static_cast<PeepNauseaTolerance>(std::min<uint8_t>(value, 3));
        }
    }

    int32_t ScGuest::cash_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->CashInPocket : 0;
    }
    void ScGuest::cash_set(int32_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->CashInPocket = std::max(0, value);
        }
    }

    bool ScGuest::isInPark_get() const
    {
        auto peep = GetGuest();
        return (peep != nullptr && !peep->OutsideOfPark);
    }

    bool ScGuest::isLost_get() const
    {
        auto peep = GetGuest();
        return (peep != nullptr && peep->GuestIsLostCountdown < 90);
    }

    uint8_t ScGuest::lostCountdown_get() const
    {
        auto peep = GetGuest();
        return peep != nullptr ? peep->GuestIsLostCountdown : 0;
    }
    void ScGuest::lostCountdown_set(uint8_t value)
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->GuestIsLostCountdown = value;
        }
    }

    DukValue ScGuest::thoughts_get() const
    {
        auto ctx = GetContext()->GetScriptEngine().GetContext();

        duk_push_array(ctx);

        auto peep = GetGuest();
        if (peep != nullptr)
        {
            duk_uarridx_t index = 0;
            for (const auto& thought : peep->Thoughts)
            {
                if (thought.type == PeepThoughtType::None)
                    break;
                if (thought.freshness == 0)
                    continue;
                auto scThoughtPtr = std::make_shared<ScThought>(thought);
                auto dukThought = GetObjectAsDukValue(ctx, scThoughtPtr);
                dukThought.push();
                duk_put_prop_index(ctx, -2, index);
                index++;
            }
        }

        return DukValue::take_from_stack(ctx, -1);
    }

    DukValue ScGuest::items_get() const
    {
        auto ctx = GetContext()->GetScriptEngine().GetContext();

        duk_push_array(ctx);

        auto peep = GetGuest();
        if (peep != nullptr)
        {
            duk_uarridx_t index = 0;
            for (const auto& itemEnumPair : ShopItemMap)
            {
                auto shopItem = itemEnumPair.second;
                if (!peep->HasItem(shopItem))
                {
                    continue;
                }

                // GuestItem
                auto obj = OpenRCT2::Scripting::DukObject(ctx);
                obj.Set("type", itemEnumPair.first);

                if (shopItem == ShopItem::Voucher)
                {
                    // Voucher
                    obj.Set("voucherType", VoucherTypeMap[peep->VoucherType]);
                    if (peep->VoucherType == VOUCHER_TYPE_RIDE_FREE)
                    {
                        // RideVoucher
                        obj.Set("rideId", peep->VoucherRideId.ToUnderlying());
                    }
                    else if (peep->VoucherType == VOUCHER_TYPE_FOOD_OR_DRINK_FREE)
                    {
                        // FoodDrinkVoucher
                        obj.Set("item", ShopItemMap[peep->VoucherShopItem]);
                    }
                }
                else if (GetShopItemDescriptor(shopItem).IsPhoto())
                {
                    // GuestPhoto
                    switch (shopItem)
                    {
                        case ShopItem::Photo:
                            obj.Set("rideId", peep->Photo1RideRef.ToUnderlying());
                            break;
                        case ShopItem::Photo2:
                            obj.Set("rideId", peep->Photo2RideRef.ToUnderlying());
                            break;
                        case ShopItem::Photo3:
                            obj.Set("rideId", peep->Photo3RideRef.ToUnderlying());
                            break;
                        case ShopItem::Photo4:
                            obj.Set("rideId", peep->Photo4RideRef.ToUnderlying());
                            break;
                        default:
                            // This should not be possible
                            duk_error(ctx, DUK_ERR_TYPE_ERROR, "Item is photo without a ride ref.");
                    }
                }

                auto dukItem = obj.Take();
                dukItem.push();
                duk_put_prop_index(ctx, -2, index);
                index++;
            }
        }

        return DukValue::take_from_stack(ctx, -1);
    }

    bool ScGuest::has_item(const DukValue& item) const
    {
        auto peep = GetGuest();
        if (peep == nullptr)
        {
            return false;
        }

        if (item["type"].type() != DukValue::Type::STRING)
        {
            return false;
        }

        // GuestItem
        auto shopItem = ShopItemMap.TryGet(item["type"].as_string());
        if (!shopItem || !peep->HasItem(*shopItem))
        {
            return false;
        }

        if (*shopItem == ShopItem::Voucher)
        {
            if (item["voucherType"].type() == DukValue::Type::STRING)
            {
                // Voucher
                auto voucher = VoucherTypeMap.TryGet(item["voucherType"].as_string());
                if (!voucher || *voucher != peep->VoucherType)
                {
                    return false;
                }

                if (*voucher == VOUCHER_TYPE_RIDE_FREE)
                {
                    if (item["rideId"].type() == DukValue::Type::NUMBER)
                    {
                        // RideVoucher
                        if (item["rideId"].as_uint() != peep->VoucherRideId.ToUnderlying())
                        {
                            return false;
                        }
                    }
                }
                else if (*voucher == VOUCHER_TYPE_FOOD_OR_DRINK_FREE)
                {
                    if (item["item"].type() == DukValue::Type::STRING)
                    {
                        // FoodDrinkVoucher
                        auto voucherItem = ShopItemMap.TryGet(item["item"].as_string());
                        if (!voucherItem || *voucherItem != peep->VoucherShopItem)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        else if (GetShopItemDescriptor(*shopItem).IsPhoto())
        {
            // GuestPhoto
            if (item["rideId"].type() == DukValue::Type::NUMBER)
            {
                switch (*shopItem)
                {
                    case ShopItem::Photo:
                        if (item["rideId"].as_uint() != peep->Photo1RideRef.ToUnderlying())
                        {
                            return false;
                        }
                        break;
                    case ShopItem::Photo2:
                        if (item["rideId"].as_uint() != peep->Photo2RideRef.ToUnderlying())
                        {
                            return false;
                        }
                        break;
                    case ShopItem::Photo3:
                        if (item["rideId"].as_uint() != peep->Photo3RideRef.ToUnderlying())
                        {
                            return false;
                        }
                        break;
                    case ShopItem::Photo4:
                        if (item["rideId"].as_uint() != peep->Photo4RideRef.ToUnderlying())
                        {
                            return false;
                        }
                        break;
                    default:
                        return false;
                }
            }
        }

        return true;
    }

    void ScGuest::give_item(const DukValue& item) const
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep == nullptr)
        {
            return;
        }

        // GuestItem
        if (item["type"].type() != DukValue::Type::STRING)
        {
            auto ctx = GetContext()->GetScriptEngine().GetContext();
            duk_error(ctx, DUK_ERR_ERROR, "Invalid 'type'.");
        }

        auto shopItem = ShopItemMap.TryGet(item["type"].as_string());
        if (!shopItem)
        {
            auto ctx = GetContext()->GetScriptEngine().GetContext();
            duk_error(ctx, DUK_ERR_ERROR, "Invalid 'type'.");
        }

        if (*shopItem == ShopItem::Voucher)
        {
            // Voucher
            if (item["voucherType"].type() != DukValue::Type::STRING)
            {
                auto ctx = GetContext()->GetScriptEngine().GetContext();
                duk_error(ctx, DUK_ERR_ERROR, "Invalid 'voucherType'.");
            }

            auto voucherType = VoucherTypeMap.TryGet(item["voucherType"].as_string());
            if (!voucherType)
            {
                auto ctx = GetContext()->GetScriptEngine().GetContext();
                duk_error(ctx, DUK_ERR_ERROR, "Invalid 'voucherType'.");
            }

            if (*voucherType == VOUCHER_TYPE_RIDE_FREE)
            {
                // RideVoucher
                if (item["rideId"].type() != DukValue::Type::NUMBER)
                {
                    auto ctx = GetContext()->GetScriptEngine().GetContext();
                    duk_error(ctx, DUK_ERR_ERROR, "Invalid 'rideId'.");
                }

                peep->VoucherRideId = RideId::FromUnderlying(item["rideId"].as_uint());
            }
            else if (*voucherType == VOUCHER_TYPE_FOOD_OR_DRINK_FREE)
            {
                // FoodDrinkVoucher
                if (item["item"].type() != DukValue::Type::STRING)
                {
                    auto ctx = GetContext()->GetScriptEngine().GetContext();
                    duk_error(ctx, DUK_ERR_ERROR, "Invalid 'item' (for food/drink voucher).");
                }

                auto voucherItem = ShopItemMap.TryGet(item["item"].as_string());
                if (!voucherItem)
                {
                    auto ctx = GetContext()->GetScriptEngine().GetContext();
                    duk_error(ctx, DUK_ERR_ERROR, "Invalid 'item' (for food/drink voucher).");
                }

                peep->VoucherShopItem = *voucherItem;
            }

            peep->VoucherType = *voucherType;
        }
        else if (GetShopItemDescriptor(*shopItem).IsPhoto())
        {
            // GuestPhoto
            if (item["rideId"].type() != DukValue::Type::NUMBER)
            {
                auto ctx = GetContext()->GetScriptEngine().GetContext();
                duk_error(ctx, DUK_ERR_ERROR, "Invalid 'rideId'.");
            }

            switch (*shopItem)
            {
                case ShopItem::Photo:
                    peep->Photo1RideRef = RideId::FromUnderlying(item["rideId"].as_uint());
                    break;
                case ShopItem::Photo2:
                    peep->Photo2RideRef = RideId::FromUnderlying(item["rideId"].as_uint());
                    break;
                case ShopItem::Photo3:
                    peep->Photo3RideRef = RideId::FromUnderlying(item["rideId"].as_uint());
                    break;
                case ShopItem::Photo4:
                    peep->Photo4RideRef = RideId::FromUnderlying(item["rideId"].as_uint());
                    break;
                default:
                    return;
            }
        }

        peep->GiveItem(*shopItem);
        peep->UpdateSpriteType();
    }

    void ScGuest::remove_item(const DukValue& item) const
    {
        ThrowIfGameStateNotMutable();
        if (has_item(item))
        {
            // Since guests can only have one item of a type and this item matches, remove it.
            auto peep = GetGuest();
            peep->RemoveItem(ShopItemMap[item["type"].as_string()]);
            peep->UpdateSpriteType();
        }
    }

    void ScGuest::remove_all_items() const
    {
        ThrowIfGameStateNotMutable();
        auto peep = GetGuest();
        if (peep != nullptr)
        {
            peep->RemoveAllItems();
            peep->UpdateSpriteType();
        }
    }

    ScThought::ScThought(PeepThought backing)
        : _backing(backing)
    {
    }

    void ScThought::Register(duk_context* ctx)
    {
        dukglue_register_property(ctx, &ScThought::type_get, nullptr, "type");
        dukglue_register_property(ctx, &ScThought::item_get, nullptr, "item");
        dukglue_register_property(ctx, &ScThought::freshness_get, nullptr, "freshness");
        dukglue_register_property(ctx, &ScThought::freshTimeout_get, nullptr, "freshTimeout");
        dukglue_register_method(ctx, &ScThought::toString, "toString");
    }

    std::string ScThought::type_get() const
    {
        return std::string(ThoughtTypeMap[_backing.type]);
    }

    uint16_t ScThought::item_get() const
    {
        return _backing.item;
    }

    uint8_t ScThought::freshness_get() const
    {
        return _backing.freshness;
    }

    uint8_t ScThought::freshTimeout_get() const
    {
        return _backing.fresh_timeout;
    }

    std::string ScThought::toString() const
    {
        // format string with arguments
        auto ft = Formatter();
        PeepThoughtSetFormatArgs(&_backing, ft);
        return FormatStringID(STR_STRINGID, ft.Data());
    }

} // namespace OpenRCT2::Scripting

#endif
