using System.Diagnostics;

foreach (Process process in Process.GetProcesses())
{
    Console.WriteLine($"Id: {process.Id} Name: {process.ProcessName}");
}

Process proc = Process.GetProcessesByName("devenv")[0];
ProcessThreadCollection processThreads = proc.Threads;

foreach (ProcessThread thread in processThreads)
{
    Console.WriteLine($"ThreadId: {thread.Id}");
}

Process.Start("notepad.exe");
Process.Start("explorer", "https://www.google.com");