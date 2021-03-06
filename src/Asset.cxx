//
// Made by secondwtq <lovejay-lovemusic@outlook.com> with Love.
//
// Date: 2015-05-26
// Copyright (c) 2015 SCU ISDC All rights reserved.
//
// This file is part of the HOWARD11 Game Engine.
//
// WE ARE STANDING ON THE EDGE.
//

#include "Asset.hxx"

#include "FSM/FSMHelper.hxx"
#include "Dwight/SceneManager.hxx"

#include "Dwight/Foundation.hxx"

namespace Howard {

using namespace FSMHelper;

constexpr const char Asset::m_asset_type[];

Asset::Asset(const char *name) : m_name(name) {
    if (Foundation.assetManager().already_has(name)) {
        log("AssetMangaer", Error) << "Asset name duplicate: [" << name << "], " <<
                this->asset_type() << " & " << Foundation.assetManager().named(name)->asset_type()
                << rn;
    } else {
        this->AssetID = Foundation.assetManager().allocate_site();
        Foundation.assetManager().init_site(this->AssetID, name, this);
    }
}

}