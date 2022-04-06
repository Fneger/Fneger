#ifndef IOSERVICECLASS_H
#define IOSERVICECLASS_H

#include <vector>
#include "boost/asio.hpp"
#include "boost/thread.hpp"
#include "boost/scoped_array.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/noncopyable.hpp"

typedef boost::asio::io_service IO_Service;
typedef boost::asio::io_service::work IO_Service_work;

class IOServiceClass : public boost::noncopyable
{
public:
    explicit IOServiceClass(int size = 1)
        : work_(service_), stoped_(false){
        if (size < 1) size = 1;
        addThread(size);
    }

    ~IOServiceClass() {
        if(!stoped_){
            service_.stop();
            stoped_ = true;
        }
        threadlist_.clear();
    }
    size_t setThreadSize(size_t size = 0) {
        size_t csize = getThreadSize();
        if (size <= csize) {
            return csize;
        } else {
            addThread(csize - size);
            return size;
        }
    }
    size_t getThreadSize() const {return threadlist_.size();}
    IO_Service & getService() { return service_;}

    void stop(){
        if(!stoped_){
            service_.stop();
            for(auto t : threadlist_) t->join();
            stoped_ = true;
        }

    }

    template<typename F, typename...Args>
     void post(F &&f, Args&&...args) {
         service_.post(boost::bind(boost::forward<F>(f), boost::forward<Args>(args)...));
     }

protected:
    void addThread(int size){
        for (int i = 0; i < size; ++i) {
            boost::shared_ptr<boost::thread> th = boost::make_shared<boost::thread>
                    (boost::bind(static_cast<std::size_t (IO_Service::*)()>(&IO_Service::run), &service_));
            threadlist_.push_back(th);
            th->detach();
            }
    }
private:
    IO_Service service_;
    IO_Service_work work_;
    std::vector<boost::shared_ptr<boost::thread>> threadlist_;
    bool stoped_;
};

#endif // IOSERVICECLASS_H
