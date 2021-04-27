#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../src/treeml/tree_ext.hpp"

namespace{
tst::set set("read_ext", [](auto& suite){
	suite.add("correct_extra_info_is_provided", [](){
		const auto tml = treeml::read_ext(R"qwertyuiop(
			hello"world!"
			how {are you "doing"?
			}I'm okay
		)qwertyuiop");

		tst::check_eq(tml.size(), size_t(5), SL);

		auto& hello = tml[0];
		tst::check_eq(hello.value.to_string(), std::string("hello"), SL);
		tst::check(hello.value.get_info().flags.get(treeml::flag::space), SL);
		tst::check(!hello.value.get_info().flags.get(treeml::flag::quoted), SL);
		tst::check(!hello.value.get_info().flags.get(treeml::flag::raw_cpp), SL);

		auto& world = tml[1];
		tst::check_eq(world.value.to_string(), std::string("world!"), SL);
		tst::check(world.value.get_info().flags.get(treeml::flag::quoted), SL);
		tst::check(!world.value.get_info().flags.get(treeml::flag::space), SL);
		tst::check(!world.value.get_info().flags.get(treeml::flag::raw_cpp), SL);

		auto& how = tml[2];
		tst::check_eq(how.value.to_string(), std::string("how"), SL);
		tst::check(how.value.get_info().flags.get(treeml::flag::space), SL);
		tst::check(!how.value.get_info().flags.get(treeml::flag::quoted), SL);
		tst::check(!how.value.get_info().flags.get(treeml::flag::raw_cpp), SL);

		{
			tst::check_eq(how.children.size(), size_t(4), SL);

			auto& doing = how.children[2];
			tst::check_eq(doing.value.to_string(), std::string("doing"), SL);
			tst::check(doing.value.get_info().flags.get(treeml::flag::space), SL);
			tst::check(doing.value.get_info().flags.get(treeml::flag::quoted), SL);
			tst::check(!doing.value.get_info().flags.get(treeml::flag::raw_cpp), SL);

			auto& qm = how.children[3];
			tst::check_eq(qm.value.to_string(), std::string("?"), SL);
			tst::check(!qm.value.get_info().flags.get(treeml::flag::space), SL);
			tst::check(!qm.value.get_info().flags.get(treeml::flag::quoted), SL);
			tst::check(!qm.value.get_info().flags.get(treeml::flag::raw_cpp), SL);
		}

		auto& im = tml[3];
		tst::check_eq(im.value.to_string(), std::string("I'm"), SL);
		tst::check(!im.value.get_info().flags.get(treeml::flag::space), SL);
		tst::check(!im.value.get_info().flags.get(treeml::flag::quoted), SL);
		tst::check(!im.value.get_info().flags.get(treeml::flag::raw_cpp), SL);

		auto& okay = tml[4];
		tst::check_eq(okay.value.to_string(), std::string("okay"), SL);
	});
});
}