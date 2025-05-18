package net.davoleo.mutationtesting;

import net.davoleo.mutationtesting.mutants.*;
import org.junit.jupiter.api.Nested;

public class MutationQuickSortTest {


    @Nested
    class CleanQuickSortTest extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new QuickSort();
        }
    }


    @Nested
    class TestMutant1 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant1();
        }
    }

    @Nested
    class TestMutant2 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant2();
        }
    }

    @Nested
    class TestMutant3 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant3();
        }
    }

    @Nested
    class TestMutant4 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant4();
        }
    }

    @Nested
    class TestMutant5 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant5();
        }
    }

    @Nested
    class TestMutant6 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant6();
        }
    }

    @Nested
    class TestMutant7 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant7();
        }
    }

    @Nested
    class TestMutant8 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant8();
        }
    }

    @Nested
    class TestMutant9 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant9();
        }
    }

    @Nested
    class TestMutant10 extends AbstractQuickSortTest {
        @Override
        protected IQuickSort createInstance() {
            return new Mutant10();
        }
    }

}
