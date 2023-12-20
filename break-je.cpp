#include <stdio.h>
#include <stdlib.h>
#include <cstring>

class base
{
    private:

        char buf[32];

    public:

        void
        copy(const char *str)
        {
            strcpy(buf, str);
        }
        
        virtual void
        print(void)
        {
            printf("buf: 0x%08x: %s\n", buf, buf);
        }
};

class derived_a : public base
{
    public:

        void
        print(void)
        {
            printf("[+] derived_a: ");
            base::print();
        }
};

class derived_b : public base
{
    public:

        void
        print(void)
        {
            printf("[+] derived_b: ");
            base::print();
        }
};

int
main(int argc, char *argv[])
{
    base *obj_a;
    base *obj_b;

    obj_a = new derived_a;
    obj_b = new derived_b;

    printf("[+] obj_a:\t0x%x\n", (unsigned int)obj_a);
    printf("[+] obj_b:\t0x%x\n", (unsigned int)obj_b);

    if(argc == 3)
    {
        printf("[+] overflowing from obj_a into obj_b\n");
        obj_a->copy(argv[1]);

        obj_b->copy(argv[2]);

        obj_a->print();
        obj_b->print();

        return 0;
    }

}