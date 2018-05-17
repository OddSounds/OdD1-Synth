#ifndef WAVETABLES_H_
#define WAVETABLES_H_

#include <avr/pgmspace.h>

enum
{
	WAVE_SINE = 0,
	WAVE_TRI,
	WAVE_LSAW,
	WAVE_RSAW,
	WAVE_SQU,
	NUM_WAVE
}WAVE_TYPE;

PROGMEM const char analogWaveTable[]  = 
{
	//sine wave
	0-128,0-128,0-128,0-128,1-128,1-128,1-128,2-128,2-128,3-128,4-128,5-128,5-128,6-128,7-128,9-128,10-128,11-128,12-128,14-128,15-128,16-128,18-128,20-128,21-128,23-128,25-128,27-128,29-128,31-128,33-128,35-128,37-128,39-128,42-128,44-128,46-128,49-128,51-128,54-128,56-128,59-128,62-128,64-128,67-128,
	70-128,73-128,76-128,78-128,81-128,84-128,87-128,90-128,93-128,96-128,99-128,102-128,105-128,108-128,111-128,115-128,118-128,121-128,124-128,127-128,130-128,133-128,136-128,139-128,143-128,146-128,149-128,152-128,155-128,158-128,161-128,164-128,
	167-128,170-128,173-128,176-128,178-128,181-128,184-128,187-128,190-128,192-128,195-128,198-128,200-128,203-128,205-128,208-128,210-128,212-128,215-128,217-128,219-128,221-128,223-128,225-128,227-128,229-128,231-128,233-128,234-128,236-128,
	238-128,239-128,240-128,242-128,243-128,244-128,245-128,247-128,248-128,249-128,249-128,250-128,251-128,252-128,252-128,253-128,253-128,253-128,254-128,254-128,254-128,254-128,254-128,254-128,254-128,253-128,253-128,253-128,252-128,252-128,
	251-128,250-128,249-128,249-128,248-128,247-128,245-128,244-128,243-128,242-128,240-128,239-128,238-128,236-128,234-128,233-128,231-128,229-128,227-128,225-128,223-128,221-128,219-128,217-128,215-128,212-128,210-128,208-128,205-128,
	203-128,200-128,198-128,195-128,192-128,190-128,187-128,184-128,181-128,178-128,176-128,173-128,170-128,167-128,164-128,161-128,158-128,155-128,152-128,149-128,146-128,143-128,139-128,136-128,133-128,130-128,127-128,124-128,121-128,
	118-128,115-128,111-128,108-128,105-128,102-128,99-128,96-128,93-128,90-128,87-128,84-128,81-128,78-128,76-128,73-128,70-128,67-128,64-128,62-128,59-128,56-128,54-128,51-128,49-128,46-128,44-128,42-128,39-128,37-128,35-128,33-128,31-128,29-128,27-128,25-128,
	23-128,21-128,20-128,18-128,16-128,15-128,14-128,12-128,11-128,10-128,9-128,7-128,6-128,5-128,5-128,4-128,3-128,2-128,2-128,1-128,1-128,1-128,0-128,0-128,0-128,

	//triangle wave
	128-128,129-128,131-128,133-128,135-128,137-128,139-128,141-128,144-128,146-128,148-128,150-128,152-128,154-128,157-128,159-128,161-128,164-128,166-128,168-128,170-128,173-128,175-128,
	177-128,179-128,181-128,183-128,185-128,187-128,189-128,191-128,193-128,195-128,197-128,198-128,200-128,202-128,204-128,206-128,208-128,210-128,213-128,215-128,217-128,220-128,222-128,
	224-128,227-128,229-128,232-128,234-128,237-128,239-128,241-128,244-128,246-128,248-128,249-128,251-128,252-128,253-128,254-128,255-128,255-128,255-128,255-128,254-128,254-128,253-128,
	251-128,250-128,248-128,247-128,245-128,243-128,240-128,238-128,236-128,233-128,231-128,228-128,226-128,223-128,221-128,218-128,216-128,214-128,212-128,209-128,207-128,205-128,203-128,
	201-128,199-128,197-128,196-128,194-128,192-128,190-128,188-128,186-128,184-128,182-128,180-128,178-128,176-128,174-128,171-128,169-128,167-128,165-128,162-128,160-128,158-128,156-128,
	153-128,151-128,149-128,147-128,145-128,142-128,140-128,138-128,136-128,134-128,132-128,130-128,128-128,127-128,125-128,123-128,121-128,119-128,117-128,115-128,113-128,110-128,108-128,
	106-128,104-128,102-128,99-128,97-128,95-128,93-128,90-128,88-128,86-128,84-128,81-128,79-128,77-128,75-128,73-128,71-128,69-128,67-128,65-128,63-128,61-128,59-128,58-128,56-128,54-128,52-128,50-128,48-128,46-128,
	43-128,41-128,39-128,37-128,34-128,32-128,29-128,27-128,24-128,22-128,19-128,17-128,15-128,12-128,10-128,8-128,7-128,5-128,4-128,2-128,1-128,1-128,0-128,0-128,0-128,0-128,1-128,2-128,3-128,4-128,6-128,7-128,9-128,11-128,14-128,16-128,18-128,
	21-128,23-128,26-128,28-128,31-128,33-128,35-128,38-128,40-128,42-128,45-128,47-128,49-128,51-128,53-128,55-128,57-128,58-128,60-128,62-128,64-128,66-128,68-128,70-128,72-128,74-128,76-128,78-128,80-128,82-128,85-128,
	87-128,89-128,91-128,94-128,96-128,98-128,101-128,103-128,105-128,107-128,109-128,111-128,114-128,116-128,118-128,120-128,122-128,124-128,126-128,127-128,

	//left saw (negative slope)
	87-128,87-128,87-128,87-128,87-128,86-128,86-128,85-128,84-128,83-128,81-128,80-128,78-128,77-128,75-128,73-128,71-128,69-128,68-128,66-128,65-128,64-128,63-128,62-128,61-128,61-128,61-128,61-128,61-128,61-128,61-128,61-128,61-128,61-128,
	61-128,61-128,60-128,60-128,59-128,57-128,56-128,55-128,53-128,51-128,49-128,47-128,46-128,44-128,42-128,41-128,39-128,38-128,37-128,37-128,36-128,36-128,36-128,36-128,37-128,37-128,38-128,38-128,39-128,39-128,39-128,39-128,39-128,39-128,
	38-128,37-128,35-128,34-128,32-128,30-128,28-128,26-128,24-128,22-128,20-128,19-128,17-128,16-128,16-128,15-128,15-128,16-128,17-128,18-128,19-128,21-128,23-128,24-128,26-128,28-128,29-128,30-128,30-128,31-128,30-128,29-128,28-128,26-128,
	24-128,21-128,18-128,15-128,12-128,8-128,6-128,3-128,1-128,0-128,0-128,1-128,3-128,6-128,11-128,17-128,24-128,33-128,43-128,54-128,66-128,80-128,94-128,108-128,123-128,138-128,153-128,167-128,181-128,194-128,207-128,218-128,227-128,236-128,
	243-128,248-128,252-128,254-128,255-128,255-128,253-128,250-128,246-128,242-128,237-128,232-128,226-128,220-128,215-128,209-128,204-128,200-128,196-128,193-128,190-128,188-128,186-128,185-128,185-128,185-128,
	185-128,185-128,186-128,186-128,187-128,187-128,187-128,187-128,186-128,186-128,184-128,183-128,181-128,179-128,176-128,173-128,171-128,168-128,165-128,162-128,159-128,157-128,155-128,153-128,151-128,150-128,
	148-128,148-128,147-128,147-128,147-128,147-128,147-128,147-128,147-128,147-128,147-128,147-128,146-128,145-128,144-128,143-128,142-128,140-128,138-128,136-128,134-128,132-128,130-128,128-128,126-128,124-128,
	122-128,121-128,119-128,118-128,117-128,117-128,116-128,116-128,116-128,115-128,115-128,115-128,115-128,115-128,115-128,115-128,114-128,114-128,113-128,112-128,111-128,109-128,108-128,106-128,104-128,102-128,
	100-128,98-128,97-128,95-128,93-128,92-128,91-128,90-128,89-128,88-128,88-128,87-128,87-128,87-128,87-128,87-128,


	//right saw (positive slope)
	168-128,168-128,168-128,168-128,168-128,169-128,169-128,170-128,171-128,172-128,174-128,175-128,177-128,178-128,180-128,182-128,184-128,186-128,187-128,189-128,190-128,191-128,192-128,
	193-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,194-128,195-128,195-128,196-128,198-128,199-128,200-128,202-128,204-128,206-128,208-128,
	209-128,211-128,213-128,214-128,216-128,217-128,218-128,218-128,219-128,219-128,219-128,219-128,218-128,218-128,217-128,217-128,216-128,216-128,216-128,216-128,216-128,216-128,217-128,
	218-128,220-128,221-128,223-128,225-128,227-128,229-128,231-128,233-128,235-128,236-128,238-128,239-128,239-128,240-128,240-128,239-128,238-128,237-128,236-128,234-128,232-128,231-128,
	229-128,227-128,226-128,225-128,225-128,224-128,225-128,226-128,227-128,229-128,231-128,234-128,237-128,240-128,243-128,247-128,249-128,252-128,254-128,255-128,255-128,254-128,252-128,
	249-128,244-128,238-128,231-128,222-128,212-128,201-128,189-128,175-128,161-128,147-128,132-128,117-128,102-128,88-128,74-128,61-128,48-128,37-128,28-128,19-128,12-128,7-128,3-128,1-128,0-128,0-128,2-128,
	5-128,9-128,13-128,18-128,23-128,29-128,35-128,40-128,46-128,51-128,55-128,59-128,62-128,65-128,67-128,69-128,70-128,70-128,70-128,70-128,70-128,69-128,69-128,68-128,68-128,68-128,68-128,69-128,69-128,71-128,72-128,
	74-128,76-128,79-128,82-128,84-128,87-128,90-128,93-128,96-128,98-128,100-128,102-128,104-128,105-128,107-128,107-128,108-128,108-128,108-128,108-128,108-128,108-128,108-128,108-128,108-128,108-128,
	109-128,110-128,111-128,112-128,113-128,115-128,117-128,119-128,121-128,123-128,125-128,127-128,129-128,131-128,133-128,134-128,136-128,137-128,138-128,138-128,139-128,139-128,139-128,
	140-128,140-128,140-128,140-128,140-128,140-128,140-128,141-128,141-128,142-128,143-128,144-128,146-128,147-128,149-128,151-128,153-128,155-128,157-128,158-128,160-128,162-128,163-128,
	164-128,165-128,166-128,167-128,167-128,168-128,168-128,168-128,168-128,168-128,

	//Square
	127-128,141-128,154-128,167-128,180-128,192-128,203-128,213-128,222-128,230-128,237-128,243-128,247-128,251-128,253-128,255-128,255-128,255-128,253-128,251-128,249-128,246-128,243-128,240-128,237-128,234-128,232-128,
	229-128,227-128,226-128,224-128,224-128,224-128,224-128,225-128,226-128,227-128,229-128,231-128,233-128,235-128,237-128,239-128,240-128,242-128,243-128,244-128,244-128,244-128,244-128,243-128,243-128,241-128,240-128,
	238-128,237-128,235-128,233-128,232-128,230-128,229-128,228-128,227-128,227-128,227-128,227-128,228-128,228-128,230-128,231-128,232-128,234-128,236-128,238-128,239-128,241-128,242-128,243-128,244-128,244-128,244-128,
	244-128,243-128,242-128,241-128,239-128,238-128,236-128,234-128,232-128,230-128,228-128,226-128,225-128,224-128,224-128,224-128,224-128,225-128,226-128,228-128,230-128,233-128,236-128,239-128,242-128,245-128,248-128,
	250-128,252-128,254-128,255-128,255-128,254-128,252-128,249-128,245-128,240-128,234-128,226-128,217-128,208-128,197-128,186-128,174-128,161-128,148-128,134-128,121-128,107-128,94-128,81-128,69-128,58-128,47-128,38-128,
	29-128,21-128,15-128,10-128,6-128,3-128,1-128,0-128,0-128,1-128,3-128,5-128,7-128,10-128,13-128,16-128,19-128,22-128,25-128,27-128,29-128,30-128,31-128,31-128,31-128,31-128,30-128,29-128,27-128,25-128,23-128,21-128,19-128,17-128,16-128,14-128,13-128,12-128,11-128,
	11-128,11-128,11-128,12-128,13-128,14-128,16-128,17-128,19-128,21-128,23-128,24-128,25-128,27-128,27-128,28-128,28-128,28-128,28-128,27-128,26-128,25-128,23-128,22-128,20-128,18-128,17-128,15-128,14-128,12-128,12-128,11-128,11-128,11-128,11-128,12-128,
	13-128,15-128,16-128,18-128,20-128,22-128,24-128,26-128,28-128,29-128,30-128,31-128,31-128,31-128,31-128,29-128,28-128,26-128,23-128,21-128,18-128,15-128,12-128,9-128,6-128,4-128,2-128,0-128,0-128,0-128,2-128,4-128,8-128,12-128,18-128,25-128,33-128,42-128,52-128,
	63-128,75-128,88-128,101-128,114-128,127-128,
};


#endif /* WAVETABLES_H_ */