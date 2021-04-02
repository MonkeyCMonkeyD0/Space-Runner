APP = server client


all: $(APP)

server:
	@cd $@; make

client:
	@cd $@; make

clean:
	@$(foreach app, $(APP), cd $(app); make clean; cd ..;)

distclean: 
	@$(foreach app, $(APP), cd $(app); make distclean; cd ..;)

.PHONY: server client clean distclean
