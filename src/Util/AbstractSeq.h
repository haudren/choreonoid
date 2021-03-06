/**
   @file
   @author Shin'ichiro Nakaoka
*/

#ifndef CNOID_UTIL_ABSTRACT_SEQ_H
#define CNOID_UTIL_ABSTRACT_SEQ_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "exportdecl.h"

namespace cnoid {

class Mapping;
class YAMLWriter;
    
class AbstractSeq;
typedef boost::shared_ptr<AbstractSeq> AbstractSeqPtr;


class CNOID_EXPORT AbstractSeq
{
protected:
    AbstractSeq(const char* seqType);
    AbstractSeq(const AbstractSeq& org);
    
public:
    virtual ~AbstractSeq();

    virtual AbstractSeqPtr cloneSeq() const = 0;

    virtual AbstractSeq& operator=(const AbstractSeq& rhs);

    void copySeqProperties(const AbstractSeq& source);

    const std::string& seqType() const {
        return seqType_;
    }

    virtual double getFrameRate() const = 0;
    virtual void setFrameRate(double frameRate) = 0;

    double getTimeStep() const {
        return 1.0 / getFrameRate();
    }
    
    void setTimeStep(double timeStep){
        return setFrameRate(1.0 / timeStep);
    }

    double getTimeOfFrame(int frame){
        return frame / getFrameRate();
    }

    virtual int getOffsetTimeFrame() const;

    double getOffsetTime() const {
        return getOffsetTimeFrame() / getFrameRate();
    }
    
    virtual int getNumFrames() const = 0;
    virtual void setNumFrames(int n, bool clearNewElements = false) = 0;

    void setTimeLength(double length, bool clearNewElements = false){
        return setNumFrames(static_cast<int>(length * getFrameRate()), clearNewElements);
    }

    /**
       @if jp
       シーケンスの時間長を返す。
       @note この時間 *未満* の時間については有効なデータが存在する。
       この時間のデータは存在しないので、そのようなアクセスしてはいけない。
       @endif
    */
    inline double getTimeLength() const {
        return getNumFrames() / getFrameRate();
    }

    inline const std::string& seqContentName() {
        return content;
    }

    virtual void setSeqContentName(const std::string& content) {
        this->content = content;
    }

    bool readSeq(const Mapping& archive);
    bool writeSeq(YAMLWriter& writer);

    inline const std::string& seqMessage() const {
        return message;
    }

    static const double defaultFrameRate() { return 100.0; }
        
protected:

    virtual bool doReadSeq(const Mapping& archive);
    virtual bool doWriteSeq(YAMLWriter& writer);

    bool checkSeqContent(const Mapping& archive, const std::string contentName, bool throwEx = false);

    void clearSeqMessage() { message.clear(); }
        
    void addSeqMessage(const std::string& message) {
        this->message += message;
    }

private:
    std::string seqType_;
    std::string content;
    std::string message;
};


class CNOID_EXPORT AbstractMultiSeq : public AbstractSeq
{
public:
    AbstractMultiSeq(const char* seqType);
    AbstractMultiSeq(const AbstractMultiSeq& org);
    virtual ~AbstractMultiSeq();

    virtual AbstractSeqPtr cloneSeq() const = 0;

    AbstractMultiSeq& operator=(const AbstractMultiSeq& rhs);
    void copySeqProperties(const AbstractMultiSeq& source);

    virtual void setDimension(int numFrames, int numParts, bool clearNewElements = false) = 0;
            
    virtual void setNumParts(int numParts, bool clearNewElements = false) = 0;
    virtual int getNumParts() const = 0;

    virtual int partIndex(const std::string& partLabel) const;
    virtual const std::string& partLabel(int partIndex) const;

protected:
    virtual bool doWriteSeq(YAMLWriter& writer);

    typedef boost::function<void(const std::string& label, int index)> SetPartLabelFunction;
    bool readSeqPartLabels(const Mapping& archive, SetPartLabelFunction setPartLabel);
    bool writeSeqPartLabels(YAMLWriter& writer);
};

typedef boost::shared_ptr<AbstractMultiSeq> AbstractMultiSeqPtr;
}

#endif
