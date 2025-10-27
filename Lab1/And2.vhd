use ieee.std_logic_1164.all;
entity And2 is
    port (
        A : in std_logic;
        B : in std_logic;
        Y : out std_logic
    );
end entity And2;

architecture Dataflow of And2 is
    begin
        Y <= A and B;

end architecture Dataflow;
