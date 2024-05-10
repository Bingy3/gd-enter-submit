#include <Geode/Geode.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS

#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>

using namespace keybinds;

class $modify(scl, ShareCommentLayer) {
	bool init(gd::string title, int charLimit, CommentType type, int ID, gd::string desc) {
		if (!ShareCommentLayer::init(title, charLimit, type, ID, desc)) {return false;}
		
		// define
		this->defineKeybind("submit-comment"_spr, [this]() {
			this->onShare(this);
		});

		return true;
	}

	// copied from better edit
	void defineKeybind(const char* id, std::function<void()> callback) {
        this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
            if (event->isDown()) {
                callback();
            }
            return ListenerResult::Propagate;
        }, id);
    }
};

$execute {
	BindManager::get()->registerBindable(BindableAction(
		"submit-comment"_spr,
		"Submit comment",
		"Submits a comment when keybind is pressed.",
		{ Keybind::create(KEY_Enter) },
		Category::PLAY
	));
}

#endif