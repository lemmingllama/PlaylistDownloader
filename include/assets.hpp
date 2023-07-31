#pragma once
struct IncludedAsset {
    IncludedAsset(uint8_t* start, uint8_t* end) : array(reinterpret_cast<Array<uint8_t>*>(start)) {
        array->klass = nullptr;
        array->monitor = nullptr;
        array->bounds = nullptr;
        array->max_length = end - start - 32;
    }

    operator ArrayW<uint8_t>() const {
        init();
        return array;
    }
    operator std::string_view() const {
        return { reinterpret_cast<char*>(array->values), array->Length() };
    }

    operator std::span<uint8_t>() const {
        return { array->values, array->Length() };
    }
    void init() const {
        if(!array->klass)
            array->klass = classof(Array<uint8_t>*);
    }
    private:
        Array<uint8_t>* array;
};
#define DECLARE_FILE(name)                        \
    extern "C" uint8_t _binary_##name##_start[];  \
    extern "C" uint8_t _binary_##name##_end[];    \
    const IncludedAsset name { _binary_##name##_start, _binary_##name##_end};
#define PNG_SPRITE(name) \
QuestUI::BeatSaberUI::ArrayToSprite(static_cast<ArrayW<uint8_t>>(IncludedAssets::name##_png))

namespace IncludedAssets {
	DECLARE_FILE(AccSaber_png)
	DECLARE_FILE(BeatSaver_png)
	DECLARE_FILE(Hitbloq_png)
	DECLARE_FILE(filtermenu_bsml)
	DECLARE_FILE(playlistdetail_bsml)
	DECLARE_FILE(playlistlist_bsml)
}
