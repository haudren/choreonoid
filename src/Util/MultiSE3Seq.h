/**
   @file
   @author Shin'ichiro Nakaoka
*/

#ifndef CNOID_UTIL_MULTI_SE3_SEQ_H
#define CNOID_UTIL_MULTI_SE3_SEQ_H

#include "MultiSeq.h"
#include "EigenTypes.h"
#include "exportdecl.h"

namespace cnoid {

class Mapping;
class Listing;
class YAMLWriter;
        
class CNOID_EXPORT MultiSE3Seq : public MultiSeq<SE3, Eigen::aligned_allocator<SE3> >
{
    typedef MultiSeq<SE3, Eigen::aligned_allocator<SE3> > BaseSeqType;

public:
    typedef boost::shared_ptr<MultiSE3Seq> Ptr;

    MultiSE3Seq();
    MultiSE3Seq(int numFrames, int numParts = 1);
    MultiSE3Seq(const MultiSE3Seq& org);
    virtual ~MultiSE3Seq();

    virtual AbstractSeqPtr cloneSeq() const;
        
    //virtual bool loadPlainFormat(const std::string& filename);

    bool loadPlainMatrixFormat(const std::string& filename);
    bool saveTopPartAsPlainMatrixFormat(const std::string& filename);

protected:
    virtual SE3 defaultValue() const { return SE3(Vector3::Zero(), Quat::Identity()); }

    virtual bool doWriteSeq(YAMLWriter& writer);
    virtual bool doReadSeq(const Mapping& archive);

private:
    void readPosQuatSeq(int nParts, int nFrames, const Listing& values, bool isWfirst);
    void readPosRpySeq(int nParts, int nFrames, const Listing& values);
};

typedef MultiSE3Seq::Ptr MultiSE3SeqPtr;        
}

#endif
