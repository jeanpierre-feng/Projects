<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="20008000">
	<Item Name="Poste de travail" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">Poste de travail/VI Serveur</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">Poste de travail/VI Serveur</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Commande 1.ctl" Type="VI" URL="../Commande 1.ctl"/>
		<Item Name="Commande 2.ctl" Type="VI" URL="../Commande 2.ctl"/>
		<Item Name="Commande 3.ctl" Type="VI" URL="../Commande 3.ctl"/>
		<Item Name="Commande 4.ctl" Type="VI" URL="../Commande 4.ctl"/>
		<Item Name="Commande 5.ctl" Type="VI" URL="../Commande 5.ctl"/>
		<Item Name="Robot_Doseur.vi" Type="VI" URL="../Robot_Doseur.vi"/>
		<Item Name="Dépendances" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
		</Item>
		<Item Name="Spécifications de construction" Type="Build"/>
	</Item>
</Project>
