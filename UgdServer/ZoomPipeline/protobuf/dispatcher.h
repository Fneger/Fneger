// Copyright 2011, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_EXAMPLES_PROTOBUF_CODEC_DISPATCHER_H
#define MUDUO_EXAMPLES_PROTOBUF_CODEC_DISPATCHER_H

#include "boost/noncopyable.hpp"
#include "casiotcpsocket.h"
#include "Callbacks.h"

#include <google/protobuf/message.h>

#include <map>

#include <type_traits>

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class Callback : boost::noncopyable
{
 public:
  virtual ~Callback() = default;
  virtual void onMessage(const TcpSocketPtr&,
                         const MessagePtr& message) const = 0;
};

template <typename T>
class CallbackT : public Callback
{
  static_assert(boost::is_base_of<google::protobuf::Message, T>::value,
                "T must be derived from gpb::Message.");
 public:
  typedef boost::function<void (const TcpSocketPtr&,
                                const boost::shared_ptr<T>& message)> ProtobufMessageTCallback;

  CallbackT(const ProtobufMessageTCallback& callback)
    : callback_(callback)
  {
  }

  void onMessage(const TcpSocketPtr& conn,
                 const MessagePtr& message) const override
  {
      boost::shared_ptr<T> concrete = fneger::down_pointer_cast<T>(message);
      assert(concrete != NULL);
      callback_(conn, concrete);
  }

 private:
  ProtobufMessageTCallback callback_;
};

class ProtobufDispatcher
{
 public:
  typedef boost::function<void (const TcpSocketPtr&,
                                const MessagePtr& message)> ProtobufMessageCallback;

  explicit ProtobufDispatcher(const ProtobufMessageCallback& defaultCb)
    : defaultCallback_(defaultCb)
  {
  }

  void onProtobufMessage(const TcpSocketPtr& conn,
                         const MessagePtr& message) const
  {
    CallbackMap::const_iterator it = callbacks_.find(message->GetDescriptor());
    if (it != callbacks_.end())
    {
      it->second->onMessage(conn, message);
    }
    else
    {
      defaultCallback_(conn, message);
    }
  }

  template<typename T>
  void registerMessageCallback(const typename CallbackT<T>::ProtobufMessageTCallback& callback)
  {
    boost::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback));
    callbacks_[T::descriptor()] = pd;
  }

 private:
  typedef std::map<const google::protobuf::Descriptor*, boost::shared_ptr<Callback> > CallbackMap;

  CallbackMap callbacks_;
  ProtobufMessageCallback defaultCallback_;
};
#endif  // MUDUO_EXAMPLES_PROTOBUF_CODEC_DISPATCHER_H

