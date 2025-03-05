

class OperationMain {
    public: 
        OperationMain();
        /** Call init() to start */
        void init();
    private:
        int loadOrderBook();
        void printMenu();
        void printHelp();
        void printMarketStats();
        int getUserOption();
        void processUserOption(int userOption);
        void walletStatus();
    };