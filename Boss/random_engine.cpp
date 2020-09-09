#include"Boss/random_engine.hpp"
#include"Net/Fd.hpp"
#include<errno.h>
#include<fcntl.h>
#include<stdexcept>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

namespace {

std::default_random_engine initialize_random_engine() {
	auto seed = std::default_random_engine::result_type(0);

	auto dr = Net::Fd();
	do {
		dr = Net::Fd(open("/dev/random", O_RDONLY));
	} while (!dr && errno == EINTR);
	if (!dr)
		throw std::runtime_error(
			std::string("open /dev/random: ") +
			strerror(errno)
		);

	(void) read(dr.get(), &seed, sizeof(seed));

	return std::default_random_engine(seed);
}

}

namespace Boss {

std::default_random_engine random_engine = initialize_random_engine();

}
