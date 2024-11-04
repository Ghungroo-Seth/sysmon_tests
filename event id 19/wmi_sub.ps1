 $query = "select * from __instanceModificationEvent within 5 where targetInstance isa 'win32_Service'"
 $wmieventfilter = Set-WmiInstance -class __EventFilter -Namespace "root\subscription" -Arguments @{name="MyFilter123";EventNameSpace="root\cimv2";QueryLanguage="WQL";Query=$query}
 $wmieventconsumer = Set-WmiInstance -class CommandLineEventConsumer -Namespace "root\subscription" -Arguments @{Name="MyConsumer123"; ExecutablePath="C:\windows\system32\cmd.exe";CommandLineTemplate="C:\windows\system32\cmd.exe"}
 Set-WmiInstance -Class __FilterToConsumerBinding -Namespace "root\subscription" -Arguments @{Filter= $wmieventfilter; Consumer=$wmieventconsumer}
