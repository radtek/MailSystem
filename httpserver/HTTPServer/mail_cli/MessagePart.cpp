#include "MessagePart.h"
#include "../tools/GeneralUtils.h"

MessagePart::MessagePart() : mEncoding(ContentTransferEncoding::SevenBit)
{
}

MessagePart::~MessagePart()
{
	this->clearParts();
}

const ContentTransferEncoding MessagePart::getEncoding()
{
	return mEncoding;
}

const mail_content_type_t& MessagePart::getContentType()
{
	return mContentType;
}

const mail_content_disposition_t& MessagePart::getContentDisposition()
{
	return mContentDisposition;
}

const rstring& MessagePart::getMessage()
{
	return mMessage;
}

const std::list<MessagePart*> MessagePart::getParts()
{
	return mParts;
}

const int MessagePart::getPartsSize()
{
	return mParts.size();
}

const str_kvmap& MessagePart::getParams()
{
	return mParams;
}

bool MessagePart::containParam(const rstring& name)
{
	return mParams.find(name) != mParams.end();
}

const rstring& MessagePart::getParam(const rstring& name)
{
	if (containParam(name)) {
		return mParams[name];
	}
	else {
		return "";
	}
}

void MessagePart::setEncoding(ContentTransferEncoding encoding)
{
	this->mEncoding = encoding;
}

void MessagePart::setContentType(const mail_content_type_t& contenttype)
{
	this->mContentType = contenttype;
}

void MessagePart::setContentDisposition(const mail_content_disposition_t& contentDisposition)
{
	this->mContentDisposition = contentDisposition;
}

void MessagePart::setMessage(const rstring& message)
{
	this->mMessage = message;
}

void MessagePart::setParts(const std::list<MessagePart*>& parts)
{
	this->clearParts();
	this->mParts = parts;
}

void MessagePart::setParams(const str_kvmap& params)
{
	mParams = params;
}

bool MessagePart::addParam(const rstring& name, const rstring& val)
{
	if (containParam(name)) {
		return false;
	}
	else {
		mParams[name] = val;
		return true;
	}
}

bool MessagePart::setParam(const rstring& name, const rstring& val)
{
	if (containParam(name)) {
		mParams[name] = val;
		return true;
	}
	else {
		return false;
	}
}

void MessagePart::setOrAddParam(const rstring& name, const rstring& val)
{
	mParams[name] = val;
}

void MessagePart::addPartBack(MessagePart*& part)
{
	this->mParts.emplace_back(part);
}

void MessagePart::addPartFront(MessagePart*& part)
{
	this->mParts.emplace_front(part);
}

void MessagePart::clearParts()
{
	// �ͷ�ԭ��Դ
	for (MessagePart* p : mParts) {
		delete p;
	}

	mParts.clear();
}

// ��ȡ�ļ������Ǹ���Ӧ���ؿ��ַ���
const rstring& MessagePart::getFileName()
{
	return mContentDisposition.filename.size() == 0 ?
		mContentType.name : mContentDisposition.filename;
}

// �Ƿ�Ϊ multipart ����
bool MessagePart::isMultipart()
{
	return GeneralUtil::strStartWith(mContentType.media, "multipart/", true);
}

// �Ƿ�Ϊ�ı�����
bool MessagePart::isText()
{
	return mContentType.media.size() == 0 ||
		GeneralUtil::strStartWith(mContentType.media, "text/", true) ||
		(_strnicmp(mContentType.media.c_str(), "message/rfc822", mContentType.media.size()) == 0);
}

// �Ƿ�Ϊ��������
bool MessagePart::isAttachment()
{
	return (!isText() && !isMultipart()) ||
		(_strnicmp(mContentDisposition.type.c_str(), "attachment", mContentDisposition.type.size()) == 0);
}

// ��ȡ��һ��ý������Ϊ media �Ĳ���
MessagePart* MessagePart::getFirstPartOfMediaType(const rstring& media)
{
	if (mContentType.media.compare(media) == 0) {
		return this;
	}

	if (this->isMultipart()) {
		for (MessagePart* p : mParts) {
			MessagePart* found = p->getFirstPartOfMediaType(media);
			if (found != nullptr) {
				return found;
			}
		}
	}

	return nullptr;
}

// ��ȡ����ý������Ϊ media �Ĳ���
void MessagePart::getAllPartsOfMediaType(const rstring& media, std::list<MessagePart*>& parts)
{
	if (mContentType.media.compare(media) == 0) {
		parts.push_back(this);
	}

	if (this->isMultipart()) {
		for (MessagePart* p : mParts) {
			p->getAllPartsOfMediaType(media, parts);
		}
	}
}

// ��ȡ�����ı����͵Ĳ���
void MessagePart::getAllTextParts(std::list<MessagePart*>& parts)
{
	if (this->isText()) {
		parts.emplace_back(this);
	}

	if (this->isMultipart()) {
		for (MessagePart* p : mParts) {
			p->getAllTextParts(parts);
		}
	}
}

// ��ȡ���и������͵Ĳ���
void MessagePart::getAllAttachmentParts(std::list<MessagePart*>& parts)
{
	if (this->isAttachment()) {
		parts.emplace_back(this);
	}

	if (this->isMultipart()) {
		for (MessagePart* p : mParts) {
			p->getAllAttachmentParts(parts);
		}
	}
}