#ifndef _CLIENTSERVER_MESSAGE_H_
#define _CLIENTSERVER_MESSAGE_H_

#include <string>
#include <boost/serialization/base_object.hpp>

class Message
{
public:
	Message() = default;
	Message(std::string sender_, std::string text_, std::string date_)
			:text(text_), sender(sender_), date(date_) {}
	inline std::string getText() { return text; }
	inline std::string getSender() { return sender; }
	inline std::string getDate() { return date; }

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & text;
		ar & sender;
		ar & date;
	}
    
private:
	std::string text;
	std::string sender;
	std::string date;
};

#endif