//
// Generated file, do not edit! Created by nedtool 5.6 from message_structure.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "message_structure_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(MessageStructure)

MessageStructure::MessageStructure(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->messageType = 0;
    this->packetLength = 0;
    this->flowIdentifier = 0;
    this->flowSequenceIdentifier = 0;
    this->retransmissionNumber = 0;
    packetHopTracking_arraysize = 0;
    this->packetHopTracking = 0;
    packetTimingTracking_arraysize = 0;
    this->packetTimingTracking = 0;
}

MessageStructure::MessageStructure(const MessageStructure& other) : ::omnetpp::cPacket(other)
{
    packetHopTracking_arraysize = 0;
    this->packetHopTracking = 0;
    packetTimingTracking_arraysize = 0;
    this->packetTimingTracking = 0;
    copy(other);
}

MessageStructure::~MessageStructure()
{
    delete [] this->packetHopTracking;
    delete [] this->packetTimingTracking;
}

MessageStructure& MessageStructure::operator=(const MessageStructure& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MessageStructure::copy(const MessageStructure& other)
{
    this->messageType = other.messageType;
    this->packetLength = other.packetLength;
    this->flowIdentifier = other.flowIdentifier;
    this->flowSequenceIdentifier = other.flowSequenceIdentifier;
    this->retransmissionNumber = other.retransmissionNumber;
    delete [] this->packetHopTracking;
    this->packetHopTracking = (other.packetHopTracking_arraysize==0) ? nullptr : new int[other.packetHopTracking_arraysize];
    packetHopTracking_arraysize = other.packetHopTracking_arraysize;
    for (unsigned int i=0; i<packetHopTracking_arraysize; i++)
        this->packetHopTracking[i] = other.packetHopTracking[i];
    delete [] this->packetTimingTracking;
    this->packetTimingTracking = (other.packetTimingTracking_arraysize==0) ? nullptr : new ::omnetpp::simtime_t[other.packetTimingTracking_arraysize];
    packetTimingTracking_arraysize = other.packetTimingTracking_arraysize;
    for (unsigned int i=0; i<packetTimingTracking_arraysize; i++)
        this->packetTimingTracking[i] = other.packetTimingTracking[i];
}

void MessageStructure::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->packetLength);
    doParsimPacking(b,this->flowIdentifier);
    doParsimPacking(b,this->flowSequenceIdentifier);
    doParsimPacking(b,this->retransmissionNumber);
    b->pack(packetHopTracking_arraysize);
    doParsimArrayPacking(b,this->packetHopTracking,packetHopTracking_arraysize);
    b->pack(packetTimingTracking_arraysize);
    doParsimArrayPacking(b,this->packetTimingTracking,packetTimingTracking_arraysize);
}

void MessageStructure::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->packetLength);
    doParsimUnpacking(b,this->flowIdentifier);
    doParsimUnpacking(b,this->flowSequenceIdentifier);
    doParsimUnpacking(b,this->retransmissionNumber);
    delete [] this->packetHopTracking;
    b->unpack(packetHopTracking_arraysize);
    if (packetHopTracking_arraysize==0) {
        this->packetHopTracking = 0;
    } else {
        this->packetHopTracking = new int[packetHopTracking_arraysize];
        doParsimArrayUnpacking(b,this->packetHopTracking,packetHopTracking_arraysize);
    }
    delete [] this->packetTimingTracking;
    b->unpack(packetTimingTracking_arraysize);
    if (packetTimingTracking_arraysize==0) {
        this->packetTimingTracking = 0;
    } else {
        this->packetTimingTracking = new ::omnetpp::simtime_t[packetTimingTracking_arraysize];
        doParsimArrayUnpacking(b,this->packetTimingTracking,packetTimingTracking_arraysize);
    }
}

int MessageStructure::getMessageType() const
{
    return this->messageType;
}

void MessageStructure::setMessageType(int messageType)
{
    this->messageType = messageType;
}

long MessageStructure::getPacketLength() const
{
    return this->packetLength;
}

void MessageStructure::setPacketLength(long packetLength)
{
    this->packetLength = packetLength;
}

int MessageStructure::getFlowIdentifier() const
{
    return this->flowIdentifier;
}

void MessageStructure::setFlowIdentifier(int flowIdentifier)
{
    this->flowIdentifier = flowIdentifier;
}

int MessageStructure::getFlowSequenceIdentifier() const
{
    return this->flowSequenceIdentifier;
}

void MessageStructure::setFlowSequenceIdentifier(int flowSequenceIdentifier)
{
    this->flowSequenceIdentifier = flowSequenceIdentifier;
}

int MessageStructure::getRetransmissionNumber() const
{
    return this->retransmissionNumber;
}

void MessageStructure::setRetransmissionNumber(int retransmissionNumber)
{
    this->retransmissionNumber = retransmissionNumber;
}

void MessageStructure::setPacketHopTrackingArraySize(unsigned int size)
{
    int *packetHopTracking2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = packetHopTracking_arraysize < size ? packetHopTracking_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        packetHopTracking2[i] = this->packetHopTracking[i];
    for (unsigned int i=sz; i<size; i++)
        packetHopTracking2[i] = 0;
    packetHopTracking_arraysize = size;
    delete [] this->packetHopTracking;
    this->packetHopTracking = packetHopTracking2;
}

unsigned int MessageStructure::getPacketHopTrackingArraySize() const
{
    return packetHopTracking_arraysize;
}

int MessageStructure::getPacketHopTracking(unsigned int k) const
{
    if (k>=packetHopTracking_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", packetHopTracking_arraysize, k);
    return this->packetHopTracking[k];
}

void MessageStructure::setPacketHopTracking(unsigned int k, int packetHopTracking)
{
    if (k>=packetHopTracking_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", packetHopTracking_arraysize, k);
    this->packetHopTracking[k] = packetHopTracking;
}

void MessageStructure::setPacketTimingTrackingArraySize(unsigned int size)
{
    ::omnetpp::simtime_t *packetTimingTracking2 = (size==0) ? nullptr : new ::omnetpp::simtime_t[size];
    unsigned int sz = packetTimingTracking_arraysize < size ? packetTimingTracking_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        packetTimingTracking2[i] = this->packetTimingTracking[i];
    for (unsigned int i=sz; i<size; i++)
        packetTimingTracking2[i] = 0;
    packetTimingTracking_arraysize = size;
    delete [] this->packetTimingTracking;
    this->packetTimingTracking = packetTimingTracking2;
}

unsigned int MessageStructure::getPacketTimingTrackingArraySize() const
{
    return packetTimingTracking_arraysize;
}

::omnetpp::simtime_t MessageStructure::getPacketTimingTracking(unsigned int k) const
{
    if (k>=packetTimingTracking_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", packetTimingTracking_arraysize, k);
    return this->packetTimingTracking[k];
}

void MessageStructure::setPacketTimingTracking(unsigned int k, ::omnetpp::simtime_t packetTimingTracking)
{
    if (k>=packetTimingTracking_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", packetTimingTracking_arraysize, k);
    this->packetTimingTracking[k] = packetTimingTracking;
}

class MessageStructureDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MessageStructureDescriptor();
    virtual ~MessageStructureDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(MessageStructureDescriptor)

MessageStructureDescriptor::MessageStructureDescriptor() : omnetpp::cClassDescriptor("MessageStructure", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

MessageStructureDescriptor::~MessageStructureDescriptor()
{
    delete[] propertynames;
}

bool MessageStructureDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MessageStructure *>(obj)!=nullptr;
}

const char **MessageStructureDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MessageStructureDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MessageStructureDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int MessageStructureDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *MessageStructureDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageType",
        "packetLength",
        "flowIdentifier",
        "flowSequenceIdentifier",
        "retransmissionNumber",
        "packetHopTracking",
        "packetTimingTracking",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int MessageStructureDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetLength")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flowIdentifier")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "flowSequenceIdentifier")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "retransmissionNumber")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetHopTracking")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetTimingTracking")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MessageStructureDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "long",
        "int",
        "int",
        "int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **MessageStructureDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MessageStructureDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MessageStructureDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MessageStructure *pp = (MessageStructure *)object; (void)pp;
    switch (field) {
        case 5: return pp->getPacketHopTrackingArraySize();
        case 6: return pp->getPacketTimingTrackingArraySize();
        default: return 0;
    }
}

const char *MessageStructureDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MessageStructure *pp = (MessageStructure *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MessageStructureDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MessageStructure *pp = (MessageStructure *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMessageType());
        case 1: return long2string(pp->getPacketLength());
        case 2: return long2string(pp->getFlowIdentifier());
        case 3: return long2string(pp->getFlowSequenceIdentifier());
        case 4: return long2string(pp->getRetransmissionNumber());
        case 5: return long2string(pp->getPacketHopTracking(i));
        case 6: return simtime2string(pp->getPacketTimingTracking(i));
        default: return "";
    }
}

bool MessageStructureDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MessageStructure *pp = (MessageStructure *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageType(string2long(value)); return true;
        case 1: pp->setPacketLength(string2long(value)); return true;
        case 2: pp->setFlowIdentifier(string2long(value)); return true;
        case 3: pp->setFlowSequenceIdentifier(string2long(value)); return true;
        case 4: pp->setRetransmissionNumber(string2long(value)); return true;
        case 5: pp->setPacketHopTracking(i,string2long(value)); return true;
        case 6: pp->setPacketTimingTracking(i,string2simtime(value)); return true;
        default: return false;
    }
}

const char *MessageStructureDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *MessageStructureDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MessageStructure *pp = (MessageStructure *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


