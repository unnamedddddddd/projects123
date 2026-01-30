public class People
{
    protected string p_Name = "";
    protected int p_Age = 0;

    public People(string name, int age) {
        this.p_Name = name;
        this.p_Age = age;
    }

    public void sayHi() {
        Console.WriteLine($"{this.p_Name} говорит привет");
    }
    public void sayAge()
    {
        Console.WriteLine($"{this.p_Name} {this.p_Age} лет");
    }
}

public class Denis : People
{
    private string p_Group = "";

    public Denis(string name, int age, string group) : base(name, age)
    {
        this.p_Group = group;
    }

    public void sayGroup()
    {
        Console.WriteLine($"{this.p_Name} учится в группе {this.p_Group}");
    }
}

public class Program
{
    public static void Main()
    {
        Denis denis = new Denis("Denis", 18, "ИП-391к");

        denis.sayHi();
        denis.sayAge();
        denis.sayGroup();
    }
}