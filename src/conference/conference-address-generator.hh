/*
    Flexisip, a flexible SIP proxy server with media capabilities.
    Copyright (C) 2010-2023 Belledonne Communications SARL, All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <linphone++/linphone.hh>

#include "flexisip/registrar/registar-listeners.hh"
#include "flexisip/sofia-wrapper/home.hh"

#include "registrar/registrar-db.hh"

namespace flexisip {

class ConferenceServer;

class ConferenceAddressGenerator : public ContactUpdateListener,
                                   public std::enable_shared_from_this<ConferenceAddressGenerator> {
public:
	enum class State { Fetching, Binding };

	ConferenceAddressGenerator(const std::shared_ptr<linphone::ChatRoom> chatRoom,
	                           std::shared_ptr<linphone::Address> conferenceFactoryAddr,
	                           const std::string& uuid,
	                           const std::string& path,
	                           ConferenceServer* conferenceServer);

	void run();

private:
	void onRecordFound(const std::shared_ptr<Record>& r) override;
	void onError(const SipStatus& response) override;
	void onInvalid(const SipStatus&) override {
	}
	void onContactUpdated([[maybe_unused]] const std::shared_ptr<ExtendedContact>& ec) override {
	}
	void changeAddress();
	sofiasip::Home mHome;
	const std::shared_ptr<linphone::ChatRoom> mChatRoom;
	std::shared_ptr<linphone::Address> mConferenceAddr;
	std::string mUuid;
	std::string mPath;
	ConferenceServer* mConferenceServer = nullptr;
	State mState = State::Fetching;
};

} // namespace flexisip
